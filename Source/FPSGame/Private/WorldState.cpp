// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldState.h"

UWorldState::UWorldState()
{}

UWorldState::~UWorldState()
{}

const TMap<uint8_t, bool>& UWorldState::GetWorldStateVariables()
{
	return m_worldStateVariables;
}

void UWorldState::SetHumanReadableName(const FString& i_name)
{
	m_humanReadableName = i_name;
}

bool UWorldState::GetVariableValue(uint8_t i_variableID) const
{
	return *(m_worldStateVariables.Find(i_variableID));
}

void UWorldState::SetVariableValue(uint8_t i_variableID, bool i_newValue)
{
	m_worldStateVariables.Add(i_variableID, i_newValue);
}

uint8_t UWorldState::DistanceTo(const UWorldState& i_otherState) const
{
	int result = 0;

	for (const auto& keyValuePair : i_otherState.m_worldStateVariables) 
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
