// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldState.h"

UWorldState::UWorldState()
{}

UWorldState::~UWorldState()
{}

void UWorldState::AddWorldStateVariable(int VariableCode, bool Value)
{
	m_worldStateVariables.Add(VariableCode, Value);
}

void UWorldState::SetName(const FString& Name)
{
	m_humanReadableName = Name;
}

bool UWorldState::GetWorldStateVariable(int VariableCode)
{
	auto result = m_worldStateVariables.Find(VariableCode);

	if (result == nullptr)
		return false;

	else
		return *result;
}

int UWorldState::DistanceTo(const UWorldState& i_otherState) const
{
	int result = 0;

	for (const auto& keyValuePair : m_worldStateVariables) 
	{
		auto lookupResult = m_worldStateVariables.Find(keyValuePair.Key);
		
		if (lookupResult == nullptr || *(lookupResult) != keyValuePair.Value) 
		{
			result++;
		}
	}

	return result;
}


bool UWorldState::operator==(const UWorldState& i_rhs) const
{
	return (DistanceTo(i_rhs) == 0);
}
