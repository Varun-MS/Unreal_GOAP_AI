// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UActionTest.h"
#include "WorldState.h"
/**
 * 
 */

class FPSGAME_API NodeRecord
{
public:
	NodeRecord();
	NodeRecord(UWorldState* i_pWorldState, UActionTest* i_pAction, int i_costSoFar, int i_estimatedCostToTarget, int i_parentID);

	~NodeRecord();

	static int lastID;
	int ID;
	int parentID;
	int costSoFar;
	int estimatedCostToTarget;

	TWeakObjectPtr<UActionTest> p_action;
	TWeakObjectPtr<UWorldState> p_worldState;

	inline int EstimateTotalCost() { return costSoFar + estimatedCostToTarget; }
};
