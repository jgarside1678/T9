// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Terrain/SelectableTerrainActor.h"
#include "SpawnTerrainActor.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ASpawnTerrainActor : public ASelectableTerrainActor
{
	GENERATED_BODY()
public:

	ASpawnTerrainActor();


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Basics")
		class UBuildingSpawnComponent* SpawnComponent;

public:
};
