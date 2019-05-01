// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"

#include "WorldStateDefiner.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPSGAME_API UWorldStateDefiner : public UObject
{
	GENERATED_BODY()

public:
	UWorldStateDefiner();
	~UWorldStateDefiner();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool ReevaluateDefiner();

	FString DebugName;
	int ID;
	bool IsTrue;
};

FORCEINLINE bool operator== (const UWorldStateDefiner& i_lhs, const UWorldStateDefiner& i_rhs) { return (i_lhs.IsTrue == i_rhs.IsTrue); }

FORCEINLINE bool operator!= (const UWorldStateDefiner& i_lhs, const UWorldStateDefiner& i_rhs) { return (i_lhs.IsTrue != i_rhs.IsTrue); }
