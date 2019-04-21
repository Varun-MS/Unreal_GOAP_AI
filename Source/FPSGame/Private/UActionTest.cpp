// Fill out your copyright notice in the Description page of Project Settings.

#include "UActionTest.h"

UActionTest::UActionTest()
{
	InitializeDefaults();
}

bool UActionTest::CanInterrupt() const
{
	return canInterrupt;
}

bool UActionTest::IsComplete() const
{
	return isComplete;
}

void UActionTest::InitializeDefaults()
{
	priority = 1;
	id = -1;
	status = EStatusEnum::VE_Valid;
	queuedTime = 0.0f;
	expiryTime = 0.0f;
	isComplete = false;
	canInterrupt = false;
}

bool operator<(const UActionTest & lhs, const UActionTest & rhs)
{
	return (lhs.priority < rhs.priority);
}

bool operator<=(const UActionTest & lhs, const UActionTest & rhs)
{
	return (lhs.priority <= rhs.priority);
}

bool operator>(const UActionTest & lhs, const UActionTest & rhs)
{
	return !(lhs <= rhs);
}

bool operator>=(const UActionTest & lhs, const UActionTest & rhs)
{
	return !(lhs < rhs);
}

bool operator==(const UActionTest & lhs, const UActionTest & rhs)
{
	return (lhs.id == rhs.id);
}

bool operator!=(const UActionTest & lhs, const UActionTest & rhs)
{
	return !(lhs == rhs);
}
