// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"

#include "WorldState.generated.h"

class UWorldStateDefiner;
class UWorldStateManager;

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
	void AddWorldStateDefiner(uint8 VariableCode, UWorldStateDefiner* WorldStateDefiner);

	UFUNCTION(BlueprintCallable, Category = "World State")
	void SetName(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "World State")
	UWorldStateDefiner* GetWorldStateDefiner(uint8 VariableCode);

	UFUNCTION(BlueprintCallable, Category = "World State")
	FString GetName() { return HumanReadableName; }

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "World State")
	bool IsViable(UWorldStateManager* WorldStateManager);

	int DistanceTo(TWeakObjectPtr<UWorldState> i_otherState) const;
	int DistanceTo(const UWorldState& i_otherState) const;

	UPROPERTY(BlueprintReadWrite)
	TMap<uint8, UWorldStateDefiner*> WorldStateDefiners;
	
	UPROPERTY(BlueprintReadWrite)
	FString HumanReadableName;
};

bool operator== (TWeakObjectPtr<UWorldState> i_pLHS, TWeakObjectPtr<UWorldState> i_pRHS);
bool operator== (const UWorldState& i_LHS, const UWorldState& i_RHS);

