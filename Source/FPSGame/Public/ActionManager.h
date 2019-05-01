// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

class UActionTest;
class AAIController;
class UWorldStateManager;

#include "ActionManager.generated.h"

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UActionManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionManager();

	UFUNCTION(BlueprintCallable)
	void SchedulePlan(TArray<UActionTest*> Plan);

	UFUNCTION(BlueprintCallable)
	void ScheduleAction(UActionTest* Action);

	UFUNCTION(BlueprintCallable)
	void SetAIController(AAIController * AiController);

	UFUNCTION(BlueprintCallable)
	void SetWorldStateManager(UWorldStateManager * WorldStateManager);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Update(float DeltaTime);

	void PlanUpdate(float DeltaTime);
	
	bool FindActionOnActiveQueue(UActionTest* Action, bool RemoveIfFound = false);

	void SetCurrentPlan(TArray<UActionTest*> Plan);
	void ClearCurrentPlan();

protected:
	UPROPERTY()
	TArray<UActionTest*> currentPlan;
	UPROPERTY()
	TArray<UActionTest*> stagingQueue;

	UActionTest* activeAction = nullptr;

	UPROPERTY()
	TArray<UActionTest*> activeQueue;
	UPROPERTY()
	TArray<UActionTest*> pendingQueue;

private:
	AAIController * aiController = nullptr;
	UWorldStateManager * worldStateManager = nullptr;
};
