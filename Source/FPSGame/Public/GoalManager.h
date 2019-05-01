// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoalManager.generated.h"

class UWorldState;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UGoalManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoalManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Goal Manager")
	UWorldState* GetNewGoal() const;

	UFUNCTION(BlueprintCallable, Category = "Goal Manager")
	void AddGoal(UWorldState* Goal);

	UFUNCTION(BlueprintCallable, Category = "Goal Manager")
	const TArray<UWorldState*>& GetAllGoals() const;

protected:
	TArray<UWorldState*> m_goals;
};
