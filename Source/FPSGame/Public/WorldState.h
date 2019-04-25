// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"

#include "WorldState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API UWorldState : public UObject
{
	GENERATED_BODY()

public:
	UWorldState();
	~UWorldState();

	const TMap<uint8_t, bool>& GetWorldStateVariables();
	
	void SetHumanReadableName(const FString& i_name);

	bool GetVariableValue(uint8_t i_variableID) const;
	void SetVariableValue(uint8_t i_variableID, bool i_newValue);

	uint8_t DistanceTo(const UWorldState& i_otherState) const;

	bool operator== (const UWorldState& i_rhs) const;

	TMap<uint8_t, bool> m_worldStateVariables;

protected:
	float m_priority;
	FString m_humanReadableName;
};
