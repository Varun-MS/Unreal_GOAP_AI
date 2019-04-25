// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionManager.h"
#include "UActionTest.h"

// Predicate function for sorting
bool SortByPriority(const UActionTest & lhs, const UActionTest & rhs)
{
	return (lhs < rhs);
}

// Sets default values for this component's properties
UActionManager::UActionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	pendingQueue.Heapify(SortByPriority);
	activeQueue.Heapify(SortByPriority);
}


void UActionManager::ScheduleAction(UActionTest* Action)
{
	Action->status = EStatusEnum::VE_Valid;

	if (pendingQueue.Num() == 0)
	{
		pendingQueue.HeapPush(Action, SortByPriority);
		return;
	}

	for (auto & action : pendingQueue)
	{
		if (action->id == Action->id && action->priority <= Action->priority)
		{
			pendingQueue.RemoveSingle(action);

			pendingQueue.Push(Action);
			pendingQueue.Heapify(SortByPriority);

			return;
		}
	}

	pendingQueue.HeapPush(Action, SortByPriority);

}

// Called when the game starts
void UActionManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Update(DeltaTime);
}

void UActionManager::Update(float DeltaTime)
{
	//////
	// Update queued time for each action in pending
	//////
	for (auto & action : pendingQueue)
	{
		action->queuedTime += DeltaTime;

		if (action->queuedTime >= action->expiryTime)
		{
			action->status = EStatusEnum::VE_Expired;
		}
	}

	//////
	// Check for interrupts
	//////
	for (auto & action : pendingQueue)
	{
		if (activeQueue.Num() > 0 && activeQueue[0]->priority > action->priority)
		{
			// Break because highest priority action on the active queue has a higher priority
			// than the current action on the pending queue. As such interrupts won't matter.
			break;
		}

		if (action->CanInterrupt() && action->status != EStatusEnum::VE_Expired)
		{
			// Clear active queue and push this action onto it
			activeQueue.Empty();
			activeQueue.HeapPush(action, SortByPriority);

			// Remove action from pending queue
			pendingQueue.RemoveSingle(action);
			pendingQueue.Heapify(SortByPriority);

			// Break because no other action in the pending queue can be of a higher priority
			break;
		}
	}

	//////
	// Finally RUN all active actions
	//////
	for (auto & action : activeQueue)
	{
		if (action->status == EStatusEnum::VE_Complete)
			continue;

		action->Execute();
	}

	//////
	// Cleanup on pending queue
	//////
	for (int i = pendingQueue.Num() - 1; i >= 0; --i)
	{
		if (pendingQueue[i]->status == EStatusEnum::VE_Expired)
			pendingQueue.RemoveAt(i, 1, false);
	}

	pendingQueue.Heapify(SortByPriority);

	//////
	// Cleanup on active queue
	//////
	for (int i = activeQueue.Num() - 1; i >= 0; --i)
	{
		if (activeQueue[i]->status == EStatusEnum::VE_Complete)
			activeQueue.RemoveAt(i, 1, false);
	}

	activeQueue.Heapify(SortByPriority);
}

