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
	NodeRecord(TWeakObjectPtr<UWorldState> i_pWorldState, TWeakObjectPtr<UActionTest> i_pAction, int i_costSoFar, int i_estimatedCostToTarget, int i_parentID);

	~NodeRecord();

	static int lastID;
	int ID;
	int parentID;
	int costSoFar;
	int estimatedCostToTarget;

	TWeakObjectPtr<UActionTest> pAction;
	TWeakObjectPtr<UWorldState> pWorldState;

	FORCEINLINE int EstimateTotalCost() const { return costSoFar + estimatedCostToTarget; }
};

bool operator< (const NodeRecord& i_lhs, const NodeRecord& i_rhs);
