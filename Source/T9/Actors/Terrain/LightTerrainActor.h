// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Terrain/TerrainActor.h"
#include "LightTerrainActor.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ALightTerrainActor : public ATerrainActor
{
	GENERATED_BODY()

public:
	ALightTerrainActor();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain Basics", Meta = (AllowPrivateAccess = "true"))
		class UPointLightComponent* LightComponent;

public:

};
