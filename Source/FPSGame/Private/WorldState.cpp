// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldState.h"
#include "WorldStateDefiner.h"

UWorldState::UWorldState()
{}

UWorldState::~UWorldState()
{}

void UWorldState::AddWorldStateDefiner(uint8 VariableCode, UWorldStateDefiner* WorldStateDefiner)
{
	if (WorldStateDefiners.Contains(VariableCode))
	{
		WorldStateDefiners[VariableCode]->IsTrue = WorldStateDefiner->IsTrue;
	}
	else
	{
		WorldStateDefiners.Add(VariableCode, WorldStateDefiner);
	}
}

void UWorldState::SetName(const FString& Name)
{
	HumanReadableName = Name;
}

UWorldStateDefiner* UWorldState::GetWorldStateDefiner(uint8 VariableCode)
{
	auto result = WorldStateDefiners.Find(VariableCode);

	if (result == nullptr)
		return nullptr;

	else
		return (*result);
}

int UWorldState::DistanceTo(TWeakObjectPtr<UWorldState> i_otherState) const
{
	int result = 0;

	for (const auto& keyValuePair : WorldStateDefiners) 
	{
		auto lookupResult = i_otherState->WorldStateDefiners.Find(keyValuePair.Key);
		
		if (lookupResult == nullptr || (**lookupResult) != (*keyValuePair.Value)) 
		{
			result++;
		}
	}

	return result;
}

int UWorldState::DistanceTo(const UWorldState& i_otherState) const
{
	int result = 0;

	for (const auto& keyValuePair : WorldStateDefiners)
	{
		auto lookupResult = i_otherState.WorldStateDefiners.Find(keyValuePair.Key);

		if (lookupResult == nullptr || (**lookupResult) != (*keyValuePair.Value))
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
		UWorldState* debugptr1 = i_pLHS.Get();
		UWorldState* debugptr2 = i_pRHS.Get();
		int debugDistance = i_pLHS->DistanceTo(i_pRHS);
		return (i_pLHS->DistanceTo(i_pRHS) == 0);
	}
	else
	{
		return false;
	}
}

bool operator== (const UWorldState& i_LHS, const UWorldState& i_RHS)
{
	int debugDistance = i_LHS.DistanceTo(i_RHS);
	return (i_LHS.DistanceTo(i_RHS) == 0);
}