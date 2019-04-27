// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "WorldState.h"
#include "NodeRecord.h"

class UActionTest;

#include "Planner.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API UPlanner : public UObject
{
	GENERATED_BODY()

public:
	UPlanner();
	~UPlanner();

	TArray<UActionTest> Plan(const UWorldState& i_currentState, const UWorldState& i_targetState, const TArray<UActionTest>& i_availableActions);

private:
	uint8_t EstimateCostToWorldState(const UWorldState& i_currentState, const UWorldState& i_goalState);
	void AddToOpenList(FNodeRecord&&);
	FNodeRecord& TransferToClosedList();

	bool IsWorldStateInClosedList(const UWorldState& i_state);
	bool IsWorldStateInOpenList(const UWorldState& i_state);

	TArray<FNodeRecord> m_openList;
	TArray<FNodeRecord> m_closedList;
};
