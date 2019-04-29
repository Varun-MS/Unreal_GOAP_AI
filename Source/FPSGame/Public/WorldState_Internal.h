// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <string>
#include <map>

class UWorldState;

/**
 * 
 */
class FPSGAME_API WorldState_Internal
{
public:
	WorldState_Internal();
	WorldState_Internal(UWorldState* i_UWorldState);
	~WorldState_Internal();
	
	void AddWorldStateVariable(int i_variableCode, bool i_value) { m_worldStateVariables.insert_or_assign(i_variableCode, i_value); }
	const std::map<int, bool>& GetAllWorldStateVariables() const { return m_worldStateVariables; }

	void SetName(const std::string& i_name) { m_humanReadableName = i_name; }

	bool GetWorldStateVariable(int i_variableCode) const { return m_worldStateVariables.find(i_variableCode)->second; } 

	std::string GetName() const { return m_humanReadableName; }

	int DistanceTo(const WorldState_Internal& i_otherState) const;

private:
	std::map<int, bool> m_worldStateVariables;
	std::string m_humanReadableName;

};

bool operator== (const WorldState_Internal& i_LHS, const WorldState_Internal& i_RHS);
