// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeRecord.h"

int NodeRecord::lastID = 0;

NodeRecord::NodeRecord() : costSoFar(0), estimatedCostToTarget(0)
{
	ID = ++lastID;
}

NodeRecord::NodeRecord(
	UWorldState* i_pWorldState, UActionTest* i_pAction, int i_costSoFar, int i_estimatedCostToTarget, int i_parentID
) : p_worldState(i_pWorldState), p_action(i_pAction), costSoFar(i_costSoFar), estimatedCostToTarget(i_estimatedCostToTarget), parentID(i_parentID)
{
	ID = ++lastID;
}

NodeRecord::~NodeRecord()
{
}
