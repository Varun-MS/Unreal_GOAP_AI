// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeRecord.h"

uint8_t FNodeRecord::last_id = 0;

FNodeRecord::FNodeRecord() : costSoFar(0), estimatedCostToTarget(0)
{
	id = ++last_id;
}

FNodeRecord::FNodeRecord(
	uint8_t i_parentID, UWorldState* i_pWorldState, UActionTest* i_pAction, float i_costSoFar, float i_estimatedCostToTarget
) : parentID(i_parentID), p_worldState(i_pWorldState), p_action(i_pAction), costSoFar(i_costSoFar), estimatedCostToTarget(i_estimatedCostToTarget)
{
	id = ++last_id;
}

bool operator<(const FNodeRecord& i_lhs, const FNodeRecord& i_rhs)
{
	return i_lhs.TotalEstimatedCost() < i_rhs.TotalEstimatedCost();
}
