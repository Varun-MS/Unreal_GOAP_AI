// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_Goap.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
//#include "GameFramework/Character.h"

void AAIController_Goap::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(Cast<UObject>(GetWorld()), ATargetPoint::StaticClass(), waypoints);

	//Cast<ACharacter>(GetOuter())->SpawnDefaultController();

	//GoToRandomWaypoint();
}

ATargetPoint * AAIController_Goap::GetRandomWaypoint()
{
	auto index = FMath::RandRange(0, waypoints.Num() - 1);

	return Cast<ATargetPoint>(waypoints[index]);
}

void AAIController_Goap::GoToRandomWaypoint()
{
	MoveToActor(GetRandomWaypoint());
}

