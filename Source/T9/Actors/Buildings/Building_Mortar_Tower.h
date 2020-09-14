// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/DefensiveBuildingActor.h"
#include "Building_Mortar_Tower.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ABuilding_Mortar_Tower : public ADefensiveBuildingActor
{
	GENERATED_BODY()
public:

	ABuilding_Mortar_Tower(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

	virtual void Upgrade() override;

};
