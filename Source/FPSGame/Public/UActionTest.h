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
	VE_Running		UMETA(DisplayName = "Running"),
	VE_Expired	    UMETA(DisplayName = "Expired")
};

class AAIController;

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
	bool IsRunning() const;

	UFUNCTION(BlueprintNativeEvent)
	void Execute(AAIController * aiController);

	/**
		Compare given world state against precondition,
		to determine whether this action can Act on it
	*/
	bool OperableOn(TWeakObjectPtr<UWorldState> i_pWorldState);

	/** Act on the given world state, setting existing values and/or adding new ones */
	void ActOn(TWeakObjectPtr<UWorldState> o_pWorldState) const;

	/** Add new precondition element */
	UFUNCTION(BlueprintCallable)
	void SetPrecondition(int32 key, bool value);

	/** Add new effect element */
	UFUNCTION(BlueprintCallable)
	void SetEffect(int32 key, bool value);

	/** Set cost for this action */
	UFUNCTION(BlueprintCallable)
	void SetActionCost(int32 cost);

	inline int32 GetActionCost() const { return cost; }

	/** Set the properties that will be used by the action manager */
	UFUNCTION(BlueprintCallable)
	void SetActionProperties(int32 priority, int32 id, int32 expiryTime, bool canInterrupt = false, EStatusEnum status = EStatusEnum::VE_Valid, FString name = "Action");

	/** Set a new status for this action */
	UFUNCTION(BlueprintCallable)
	void SetActionStatus(EStatusEnum status);

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
	bool isRunning;
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
