// Fill out your copyright notice in the Description page of Project Settings.

#include "GoalManager.h"
#include "WorldState.h"


// Sets default values for this component's properties
UGoalManager::UGoalManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGoalManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGoalManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UWorldState* UGoalManager::GetNewGoal(ACharacter* AICharacter) const
{
	for(auto goal : m_goals)
	{
		if (goal->IsViable())
			return goal;
	}

	return nullptr;
}

void UGoalManager::AddGoal(UWorldState* Goal)
{
	m_goals.Add(Goal);
}

const TArray<UWorldState*>& UGoalManager::GetAllGoals() const
{
	return m_goals;
}

