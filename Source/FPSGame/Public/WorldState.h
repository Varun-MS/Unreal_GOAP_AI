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

	int DistanceTo(TWeakObjectPtr<UWorldState> i_otherState) const;
	int DistanceTo(const UWorldState& i_otherState) const;

	UPROPERTY(BlueprintReadWrite)
	TMap<int, bool> WorldStateVariables;
	
	UPROPERTY(BlueprintReadWrite)
	FString HumanReadableName;

};

bool operator== (TWeakObjectPtr<UWorldState> i_pLHS, TWeakObjectPtr<UWorldState> i_pRHS);
bool operator== (const UWorldState& i_LHS, const UWorldState& i_RHS);

