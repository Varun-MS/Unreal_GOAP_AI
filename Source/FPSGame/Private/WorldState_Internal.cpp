// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldState_Internal.h"

#include "WorldState.h"

WorldState_Internal::WorldState_Internal()
{
}

WorldState_Internal::WorldState_Internal(UWorldState* i_UWorldState)
{
	for(auto keyValuePair : i_UWorldState->WorldStateVariables)
	{
		m_worldStateVariables.insert(std::make_pair(keyValuePair.Key, keyValuePair.Value));
	}
	
	m_humanReadableName = TCHAR_TO_UTF8(*(i_UWorldState->HumanReadableName));
}

WorldState_Internal::~WorldState_Internal()
{
}

int WorldState_Internal::DistanceTo(const WorldState_Internal& i_otherState) const
{
	int distance = 0;
	const auto& otherStateWorldStateVariables = i_otherState.GetAllWorldStateVariables();

	for(auto keyValuePair : m_worldStateVariables)
	{
		auto searchResult = otherStateWorldStateVariables.find(keyValuePair.first);

		if(searchResult == otherStateWorldStateVariables.end())
		{
			continue;
		}
		else
		{
			if(keyValuePair.second != searchResult->second)
			{
				distance++;
			}
		}
	}

	return distance;
}

bool operator==(const WorldState_Internal& i_LHS, const WorldState_Internal& i_RHS)
{
	return (i_LHS.DistanceTo(i_RHS) == 0);
}
