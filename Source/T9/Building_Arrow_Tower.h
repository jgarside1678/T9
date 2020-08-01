// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefensiveBuildingActor.h"
#include "Building_Arrow_Tower.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ABuilding_Arrow_Tower : public ADefensiveBuildingActor
{
	GENERATED_BODY()
public:

	ABuilding_Arrow_Tower(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

	virtual void Upgrade();



};
