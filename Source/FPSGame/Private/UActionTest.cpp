// Fill out your copyright notice in the Description page of Project Settings.

#include "UActionTest.h"
#include "WorldState.h"

//#include <stdexcept>

UActionTest::UActionTest()
{
	InitializeDefaults();
}

bool UActionTest::CanInterrupt() const
{
	return canInterrupt;
}

bool UActionTest::IsComplete() const
{
	return isComplete;
}

bool UActionTest::IsRunning() const
{
	return isRunning;
}

void UActionTest::Execute_Implementation(AAIController * aiController) {}

bool UActionTest::OperableOn(TWeakObjectPtr<UWorldState> i_pWorldState)
{
	if(!i_pWorldState.IsValid())
	{
		return false;
	}
	
	for (const auto& precond : preconditions)
	{
		/*try {
			if (worldState->GetWorldStateVariable(precond.Key) != precond.Value)
				return false;
		}
		catch (const std::out_of_range&) {
			return false;
		}*/

		// NOTE: This needs to be updated!!

		auto val = i_pWorldState->WorldStateVariables.Find(precond.Key);

		if (val != nullptr)
		{
			if (*val != precond.Value)
				return false;
		}
		else
			return false;
	}
	return true;
}

TWeakObjectPtr<UWorldState> UActionTest::ActOn(TWeakObjectPtr<UWorldState> i_pWorldState) const
{
	if (!i_pWorldState.IsValid())
	{
	}
	
	//UWorldState* newWorldState = NewObject<UWorldState>();

	for (const auto& effect : effects)
	{
		i_pWorldState->AddWorldStateVariable(effect.Key ,effect.Value);
	}

	return TWeakObjectPtr<UWorldState>();

}

void UActionTest::SetPrecondition(int32 key, bool value)
{
	if (preconditions.Contains(key))
		preconditions[key] = value;
	else
		preconditions.Add(key, value);
}

void UActionTest::SetEffect(int32 key, bool value)
{
	if (effects.Contains(key))
		effects[key] = value;
	else
		effects.Add(key, value);
}

void UActionTest::SetActionCost(int32 cost)
{
	this->cost = cost;
}

void UActionTest::SetActionProperties(int32 priority, int32 id, int32 expiryTime, bool canInterrupt, EStatusEnum status, FString name)
{
	this->priority = priority;
	this->id = id;
	this->expiryTime = expiryTime;
	this->canInterrupt = canInterrupt;
	this->status = status;
	this->name = name;
}

void UActionTest::SetActionStatus(EStatusEnum status)
{
	this->status = status;
}

void UActionTest::InitializeDefaults()
{
	priority = 1;
	id = -1;
	status = EStatusEnum::VE_Valid;
	queuedTime = 0.0f;
	expiryTime = 0.0f;
	isComplete = false;
	isRunning = false;
	canInterrupt = false;
}

bool operator<(const UActionTest & lhs, const UActionTest & rhs)
{
	return (lhs.priority < rhs.priority);
}

bool operator<=(const UActionTest & lhs, const UActionTest & rhs)
{
	return (lhs.priority <= rhs.priority);
}

bool operator>(const UActionTest & lhs, const UActionTest & rhs)
{
	return !(lhs <= rhs);
}

bool operator>=(const UActionTest & lhs, const UActionTest & rhs)
{
	return !(lhs < rhs);
}

bool operator==(const UActionTest & lhs, const UActionTest & rhs)
{
	return (lhs.id == rhs.id);
}

bool operator!=(const UActionTest & lhs, const UActionTest & rhs)
{
	return !(lhs == rhs);
}
