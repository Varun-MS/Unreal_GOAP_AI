// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeRecord.h"

int NodeRecord::lastID = 0;

NodeRecord::NodeRecord() : costSoFar(0), estimatedCostToTarget(0)
{
	ID = ++lastID;
}

NodeRecord::NodeRecord(
	TWeakObjectPtr<UWorldState> i_pWorldState, TWeakObjectPtr<UActionTest> i_pAction, int i_costSoFar, int i_estimatedCostToTarget, int i_parentID
) : pWorldState(i_pWorldState), pAction(i_pAction), costSoFar(i_costSoFar), estimatedCostToTarget(i_estimatedCostToTarget), parentID(i_parentID)
{
	ID = ++lastID;
}

NodeRecord::~NodeRecord()
{
}

bool operator<(const NodeRecord& i_lhs, const NodeRecord& i_rhs)
{
	return i_lhs.EstimateTotalCost() < i_rhs.EstimateTotalCost();
}
