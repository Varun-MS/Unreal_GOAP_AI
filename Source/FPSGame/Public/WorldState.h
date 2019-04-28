// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"

#include "WorldState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPSGAME_API UWorldState : public UObject
{
	GENERATED_BODY()

public:

	UWorldState();
	~UWorldState();

	UFUNCTION(BlueprintCallable, Category = "World State")
	void AddWorldStateVariable(int VariableCode, bool Value);

	UFUNCTION(BlueprintCallable, Category = "World State")
	void SetName(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "World State")
	bool GetWorldStateVariable(int VariableCode);

	UFUNCTION(BlueprintCallable, Category = "World State")
	FString GetName() { return HumanReadableName; }

	int DistanceTo(const UWorldState& i_otherState) const;

	bool operator== (const UWorldState& i_rhs) const;

	TMap<int, bool> WorldStateVariables;
	FString HumanReadableName;

};
