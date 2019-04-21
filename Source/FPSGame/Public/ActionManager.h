// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UActionTest.h"
#include "ActionManager.generated.h"

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UActionManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionManager();

	UFUNCTION(BlueprintCallable)
	void ScheduleAction(UActionTest* Action);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Update(float DeltaTime);
	
	TArray<UActionTest*> pendingQueue;
	TArray<UActionTest*> activeQueue;

};
