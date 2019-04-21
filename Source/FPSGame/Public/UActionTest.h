// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "UActionTest.generated.h"

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

private:
	void InitializeDefaults();


public:
	uint8 priority;
	uint8 id;

	EStatusEnum status;

	float queuedTime;
	float expiryTime;

protected:
	bool isComplete;
	bool canInterrupt;
};

bool operator < (const UActionTest &lhs, const UActionTest &rhs);
bool operator <= (const UActionTest &lhs, const UActionTest &rhs);

//bool operator () (const UActionTest &lhs, const UActionTest &rhs);

bool operator > (const UActionTest &lhs, const UActionTest &rhs);
bool operator >= (const UActionTest &lhs, const UActionTest &rhs);

// The following overloads compare Action id's instead of priority!

bool operator == (const UActionTest &lhs, const UActionTest &rhs);
bool operator != (const UActionTest &lhs, const UActionTest &rhs);
