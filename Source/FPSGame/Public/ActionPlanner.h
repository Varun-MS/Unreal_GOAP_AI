// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NodeRecord.h"
#include "WorldState.h"
#include "UActionTest.h"
#include <vector>

#include "ActionPlanner.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UActionPlanner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionPlanner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	std::vector<NodeRecord> m_openList;
	std::vector<NodeRecord> m_closedList;

	std::vector<NodeRecord>::iterator IsContainedInOpenList(WorldState_Internal i_worldState);
	bool IsContainedInClosedList(WorldState_Internal i_worldState);

	void AddToOpenList(NodeRecord&&);
	NodeRecord PopAndClose();

	int CalculateHeuristic(WorldState_Internal i_currentState, WorldState_Internal i_targetState);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TArray<UActionTest*> Plan(UWorldState* i_pCurrentState, UWorldState* i_pTargetState, const TArray<UActionTest*>& actions);
	//TArray<TWeakObjectPtr<UActionTest>> Plan(TWeakObjectPtr<UWorldState> i_pCurrentState, TWeakObjectPtr<UWorldState> i_pTargetState, const TArray<TWeakObjectPtr<UActionTest>>& actions);
};
