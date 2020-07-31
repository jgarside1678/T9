// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TerrainActor.h"
#include "Terrain_Mushroom.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ATerrain_Mushroom : public ATerrainActor
{
	GENERATED_BODY()
public:
	ATerrain_Mushroom();

};

UCLASS()
class T9_API ATerrain_Mushroom1 : public ATerrainActor {
	GENERATED_BODY()
public:
	ATerrain_Mushroom1();
};

UCLASS()
class T9_API ATerrain_Mushroom2 : public ATerrainActor {
	GENERATED_BODY()
public:
	ATerrain_Mushroom2();
};

UCLASS()
class T9_API ATerrain_MushroomHabitat : public ATerrainActor {
	GENERATED_BODY()
public:

	ATerrain_MushroomHabitat();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent3;

};