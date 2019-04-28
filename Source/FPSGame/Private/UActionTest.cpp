// Fill out your copyright notice in the Description page of Project Settings.

#include "UActionTest.h"
#include "WorldState.h"

//#include <stdexcept>

UActionTest::UActionTest()
{
	InitializeDefaults();
}

inline bool UActionTest::CanInterrupt() const
{
	return canInterrupt;
}

inline bool UActionTest::IsComplete() const
{
	return isComplete;
}

inline bool UActionTest::IsRunning() const
{
	return isRunning;
}

void UActionTest::Execute_Implementation(AAIController * aiController) {}

bool UActionTest::OperableOn(UWorldState * worldState)
{
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

		auto val = worldState->WorldStateVariables.Find(precond.Key);

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

void UActionTest::ActOn(UWorldState * worldState) const
{
	for (const auto& effect : effects)
	{
		worldState->AddWorldStateVariable(effect.Key ,effect.Value);
	}
}

void UActionTest::SetPrecondition(int32 key, bool value)
{
	preconditions[key] = value;
}

void UActionTest::SetEffect(int32 key, bool value)
{
	preconditions[key] = value;
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
