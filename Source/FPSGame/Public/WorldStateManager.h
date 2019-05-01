// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldStateManager.generated.h"

class UWorldState;
class ACharacter;

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UWorldStateManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorldStateManager();

	UFUNCTION(BlueprintCallable)
	void AddPositionToBlackboard(const FString& Name, const FVector& Position);

	UFUNCTION(BlueprintCallable)
	void AddIntegerToBlackboard(const FString& Name, int Value);

	UFUNCTION(BlueprintCallable)
	void AddRotatorToBlackboard(const FString& Name, const FRotator& Rotator);

	UFUNCTION(BlueprintCallable)
	void AddBooleanToBlackboard(const FString& Name, bool Value);

	UFUNCTION(BlueprintCallable)
	FVector GetPositionFromBlackboard(const FString& Name) const { return *(m_vectors.Find(Name)); }

	UFUNCTION(BlueprintCallable)
	int GetIntegerFromBlackboard(const FString& Name) const { return *(m_integers.Find(Name)); }

	UFUNCTION(BlueprintCallable)
	FRotator GetRotatorFromBlackboard(const FString& Name) const { return *(m_rotators.Find(Name)); }

	UFUNCTION(BlueprintCallable)
	bool GetBooleanFromBlackboard(const FString& Name) const { return *(m_booleans.Find(Name)); }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void InitializeCurrentWorldState(UWorldState* CurrentWorldState) { this->CurrentWorldState = CurrentWorldState; }

	UFUNCTION(BlueprintCallable)
	void RecalculateWorldState(ACharacter* Character);

	UPROPERTY(BlueprintReadOnly)
	UWorldState* CurrentWorldState;

protected:

	TMap<FString, FVector> m_vectors;
	TMap<FString, int> m_integers;
	TMap<FString, FRotator> m_rotators;
	TMap<FString, bool> m_booleans;
};
