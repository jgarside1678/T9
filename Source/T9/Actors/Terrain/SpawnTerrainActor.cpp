// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnTerrainActor.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"

ASpawnTerrainActor::ASpawnTerrainActor() {
	SpawnComponent = CreateDefaultSubobject<UBuildingSpawnComponent>(TEXT("Spawn Component"));
	SpawnComponent->SpawnMethod = SurroundOwner;
	SpawnComponent->MaxSpawnRange = 500;
}