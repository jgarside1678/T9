// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/DefensiveBuildingActor.h"
#include "Building_Cannon_Tower.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ABuilding_Cannon_Tower : public ADefensiveBuildingActor
{
	GENERATED_BODY()
public:

	ABuilding_Cannon_Tower(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

	virtual void Upgrade() override;


};
