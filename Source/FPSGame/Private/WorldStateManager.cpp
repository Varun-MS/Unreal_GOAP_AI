// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldStateManager.h"
#include "WorldStateDefiner.h"
#include "WorldState.h"

UWorldStateManager::UWorldStateManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWorldStateManager::AddPositionToBlackboard(const FString& Name, const FVector& Position)
{
	if (m_vectors.Contains(Name))
	{
		m_vectors[Name] = Position;
	}
	else
	{
		m_vectors.Add(Name, Position);
	}
}

void UWorldStateManager::AddIntegerToBlackboard(const FString& Name, int Value)
{
	if (m_integers.Contains(Name))
	{
		m_integers[Name] = Value;
	}
	else
	{
		m_integers.Add(Name, Value);
	}
}

void UWorldStateManager::AddRotatorToBlackboard(const FString& Name, const FRotator& Rotator)
{
	if (m_rotators.Contains(Name))
	{
		m_rotators[Name] = Rotator;
	}
	else
	{
		m_rotators.Add(Name, Rotator);
	}
}

void UWorldStateManager::AddBooleanToBlackboard(const FString& Name, bool Value)
{
	if (m_booleans.Contains(Name))
	{
		m_booleans[Name] = Value;
	}
	else
	{
		m_booleans.Add(Name, Value);
	}
}

void UWorldStateManager::BeginPlay()
{
	Super::BeginPlay();	
}


void UWorldStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto keyValuePair : (CurrentWorldState->WorldStateDefiners))
	{
		keyValuePair.Value->ReevaluateDefiner();
	}
}

