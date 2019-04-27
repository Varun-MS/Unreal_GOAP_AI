// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "UActionTest.generated.h"

class UWorldState;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EStatusEnum : uint8
{
	VE_Valid 	    UMETA(DisplayName = "Valid"),
	VE_Complete 	UMETA(DisplayName = "Complete"),
	VE_Expired	    UMETA(DisplayName = "Expired")
};

/**
 * 
 */
UCLASS(Blueprintable)
class FPSGAME_API UActionTest : public UObject
{
	GENERATED_BODY()

public:
	UActionTest();

	bool CanInterrupt() const;
	bool IsComplete() const;

	virtual void Execute() {}

	/**
		Compare given world state against precondition,
		to determine whether this action can Act on it
	*/
	bool OperableOn(const UWorldState& worldState);

	/** Act on the given world state, setting existing values and/or adding new ones */
	void ActOn(UWorldState * worldState) const;

	/** Add new precondition element */
	void SetPrecondition(int32 key, bool value);

	/** Add new effect element */
	void SetEffect(int32 key, bool value);

	/** Set the properties that will be used by the action manager */
	void SetActionProperties(int32 priority, int32 id, int32 expiryTime, bool canInterrupt = false, EStatusEnum status = EStatusEnum::VE_Valid);

	inline int32 Cost() const { return cost; }

private:
	void InitializeDefaults();

	/** Variables */
	//-------------

public:
	int32 priority;
	int32 id;

	EStatusEnum status;

	float queuedTime;
	float expiryTime;

protected:
	bool isComplete;
	bool canInterrupt;

private:

	int32 cost;

	FString name;

	TMap<int32, bool> preconditions;
	TMap<int32, bool> effects;

};

bool operator < (const UActionTest &lhs, const UActionTest &rhs);
bool operator <= (const UActionTest &lhs, const UActionTest &rhs);

//bool operator () (const UActionTest &lhs, const UActionTest &rhs);

bool operator > (const UActionTest &lhs, const UActionTest &rhs);
bool operator >= (const UActionTest &lhs, const UActionTest &rhs);

// The following overloads compare Action id's instead of priority!

bool operator == (const UActionTest &lhs, const UActionTest &rhs);
bool operator != (const UActionTest &lhs, const UActionTest &rhs);
