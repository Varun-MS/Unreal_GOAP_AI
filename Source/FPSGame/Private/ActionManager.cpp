// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionManager.h"
#include "UActionTest.h"
#include "AIController.h"
#include "Engine.h"

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

void UActionManager::SchedulePlan(TArray<UActionTest*> Plan)
{
	// check if input plan is valid
	if (Plan.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "New plan was EMPTY ... returning");
		return;
	}

	for (auto & action : Plan)
	{
		if (!action || !action->IsValidLowLevel())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "New plan was INVALID ... returning");
			return;
		}	
	}

	// If no plan was active assign input plan as current plan
	if (currentPlan.Num() == 0)
	{
		SetCurrentPlan(Plan);

		return;
	}

	// If length of plans are different => this is a new plan!
	if (currentPlan.Num() != Plan.Num())
	{
		SetCurrentPlan(Plan);

		return;
	}

	for (int i = 0; i != currentPlan.Num(); ++i)
	{
		// If even one action found that is different => this is a new plan!
		if (*currentPlan[i] != *Plan[i])
		{
			SetCurrentPlan(Plan);

			return;
		}
	}

	// Reaching here means that the plans were identical so don't do anything
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "New plan was indentical to current plan ... returning");
	return;
}

void UActionManager::ScheduleAction(UActionTest* Action)
{
	if (Action->status != EStatusEnum::VE_Valid)
		return;

	Action->queuedTime = 0.0f;

	if (pendingQueue.Num() == 0)
	{
		pendingQueue.HeapPush(Action, SortByPriority);

		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, Action->GetName());

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

void UActionManager::SetAIController(AAIController * aiController)
{
	this->aiController = aiController;
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

	//Update(DeltaTime);
	PlanUpdate(DeltaTime);
}

void UActionManager::Update(float DeltaTime)
{
	// NOTE that both the pedning queue and active queue are MIN HEAPS

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
		if (activeQueue.Num() > 0 && activeQueue.HeapTop()->priority < action->priority)
		{
			// Break because highest priority action on the active queue has a higher priority
			// than the current action on the pending queue. As such interrupts won't matter.
			continue;
		}

		if (action->CanInterrupt() && action->status != EStatusEnum::VE_Expired)
		{
			// Clear active queue and push this action onto it
			activeQueue.Empty();
			activeQueue.HeapPush(action, SortByPriority);

			// Remove action from pending queue
			pendingQueue.RemoveSingle(action);
			pendingQueue.Heapify(SortByPriority);

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Active Queue flushed!");

			// Break because no other action in the pending queue can be of a higher priority
			break;
		}
	}

	//////
	// Push new action onto the active queue if it is empty or only has finished actions
	// on it.
	// NOTE that this might be updated later to allow for concurrent actions in the active queue
	//////
	if (activeQueue.Num() == 0)
	{
		// If both queues found to be empty return from this iteration of the Update loop
		if (pendingQueue.Num() == 0)
			return;

		UActionTest* tmp;
		pendingQueue.HeapPop(tmp, SortByPriority, true);

		if (tmp != nullptr)
		{
			activeQueue.HeapPush(tmp, SortByPriority);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Active queue empty -> Pushing new action");
		}	
	}
	else
	{
		bool canPushNew = true;

		for (auto & action : activeQueue)
		{
			if (action->status != EStatusEnum::VE_Complete)
			{
				canPushNew = false;
				break;
			}
		}

		if (canPushNew && pendingQueue.Num() != 0)
		{
			UActionTest* tmp;
			pendingQueue.HeapPop(tmp, SortByPriority, true);

			if (tmp != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Active queue only has completed actions -> Pushing new action");

				activeQueue.HeapPush(tmp, SortByPriority);
			}
		}
	}

	//////
	// Finally RUN all active actions
	//////
	for (auto & action : activeQueue)
	{
		if (action->status != EStatusEnum::VE_Valid)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Skipping Complete or Running action");
			continue;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Executing action in active queue");
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Number of actions in active queue = " + FString::FromInt(activeQueue.Num()));
			action->Execute(aiController);
		}
	}

	//////
	// Cleanup on pending queue
	//////
	for (int i = pendingQueue.Num() - 1; i >= 0; --i)
	{
		if (pendingQueue[i]->status == EStatusEnum::VE_Expired)
		{
			pendingQueue.HeapRemoveAt(i, SortByPriority, true);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "CleanUp Of expired ACTION");
		}	
	}

	//////
	// Cleanup on active queue
	//////
	for (int i = activeQueue.Num() - 1; i >= 0; --i)
	{
		if (activeQueue[i]->status == EStatusEnum::VE_Complete)
		{
			activeQueue.HeapRemoveAt(i, SortByPriority, true);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "CleanUp Of Finished ACTION");
		}
	}
}

void UActionManager::PlanUpdate(float DeltaTime)
{
	// NOTE staging queue is the queue of planned actions ASSUMED to be in the correct order
	// NOTE activeAction is the action that is being executed

	/////
	// If there is no action being executed get a new action from the staging queue
	/////
	if (!activeAction)
	{
		if (stagingQueue.Num() != 0)
		{
			activeAction = stagingQueue.Pop(true);
			activeAction->status = EStatusEnum::VE_Valid;
		}
	}

	if (activeAction && activeAction->IsValidLowLevel() )
	{
		//////
		// Execute the active action if it is valid
		//////
		if (activeAction->status == EStatusEnum::VE_Valid)
			activeAction->Execute(aiController);

		//////
		// If the active action has completed, clear it
		//////
		if (activeAction->status == EStatusEnum::VE_Complete)
		{
			activeAction = nullptr;

			if (stagingQueue.Num() == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Finished executing current plan!");
				currentPlan.Empty();
			}
		}
	}
}

bool UActionManager::FindActionOnActiveQueue(UActionTest * Action, bool RemoveIfFound)
{
	int index = 0;
	if (activeQueue.Find(Action, index))
	{
		if (RemoveIfFound)
			activeQueue.HeapRemoveAt(index, SortByPriority, true);

		return true;
	}
	return false;
}

void UActionManager::SetCurrentPlan(TArray<UActionTest*> Plan)
{
	ClearCurrentPlan();

	currentPlan = Plan;

	for (auto & action : currentPlan)
	{
		action->status = EStatusEnum::VE_Valid;
	}

	stagingQueue = currentPlan;
}

void UActionManager::ClearCurrentPlan()
{
	stagingQueue.Empty();
	currentPlan.Empty();
	activeAction = nullptr;
}

