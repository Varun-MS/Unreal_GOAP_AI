// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WorldState.h"
#include "UActionTest.h"

//class UWorldState;
//class UActionTest;

#include "Engine/UserDefinedStruct.h"
#include "NodeRecord.generated.h"

/**
 * 
 */
USTRUCT()
struct FNodeRecord
{
	GENERATED_BODY()

	FNodeRecord();
	FNodeRecord(uint8_t i_parentID, UWorldState* i_pWorldState, UActionTest* i_pAction, float i_costSoFar, float i_estimatedCostToTarget);
		
	static uint8_t last_id;
		
	uint8_t id;
	uint8_t parentID;
	float costSoFar;
	float estimatedCostToTarget;
	UWorldState* p_worldState;
	UActionTest* p_action;

	inline float TotalEstimatedCost() const { return costSoFar + estimatedCostToTarget; }
};

bool operator< (const FNodeRecord& i_lhs, const FNodeRecord& i_rhs);
