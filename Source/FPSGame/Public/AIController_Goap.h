// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

#include "AIController_Goap.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AAIController_Goap : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

private:
	UPROPERTY()
		TArray<AActor*> waypoints;

	UFUNCTION(BlueprintCallable)
		ATargetPoint* GetRandomWaypoint();

	UFUNCTION(BlueprintCallable)
		void GoToRandomWaypoint();
	
};
