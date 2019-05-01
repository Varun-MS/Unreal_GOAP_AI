// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

#include "AIController_Goap.generated.h"

//UENUM(BlueprintType)		//"BlueprintType" is essential to include
//enum class EWorldStateEnum : uint8
//{
//	VE_HasLowHealth 	    UMETA(DisplayName = "HasLowHealth"),
//	VE_HasWeapon 			UMETA(DisplayName = "HasWeapon"),
//	VE_HasAmmo				UMETA(DisplayName = "HasAmmo"),
//	VE_IsEnemyVisible	    UMETA(DisplayName = "IsEnemyVisible"),
//	VE_IsEnemyDead          UMETA(DisplayName = "IsEnemyDead"),
//};

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
	UFUNCTION(BlueprintCallable)
		ATargetPoint* GetRandomWaypoint();

	UFUNCTION(BlueprintCallable)
		void GoToRandomWaypoint();

	// Member Variables
	//------

private:
	UPROPERTY()
		TArray<AActor*> waypoints;
};
