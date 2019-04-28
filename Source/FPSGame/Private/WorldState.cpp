// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldState.h"

UWorldState::UWorldState()
{}

UWorldState::~UWorldState()
{}

void UWorldState::AddWorldStateVariable(int VariableCode, bool Value)
{
	WorldStateVariables.Add(VariableCode, Value);
}

void UWorldState::SetName(const FString& Name)
{
	HumanReadableName = Name;
}

bool UWorldState::GetWorldStateVariable(int VariableCode)
{
	auto result = WorldStateVariables.Find(VariableCode);

	if (result == nullptr)
		return false;

	else
		return *result;
}

int UWorldState::DistanceTo(TWeakObjectPtr<UWorldState> i_otherState) const
{
	int result = 0;

	for (const auto& keyValuePair : WorldStateVariables) 
	{
		auto lookupResult = i_otherState->WorldStateVariables.Find(keyValuePair.Key);
		
		if (lookupResult == nullptr || *(lookupResult) != keyValuePair.Value) 
		{
			result++;
		}
	}

	return result;
}

bool operator==(TWeakObjectPtr<UWorldState> i_pLHS, TWeakObjectPtr<UWorldState> i_pRHS)
{
	if(i_pLHS.IsValid() && i_pRHS.IsValid())
	{
		return (i_pLHS->DistanceTo(i_pRHS));
	}

	else
	{
		return false;
	}
}
