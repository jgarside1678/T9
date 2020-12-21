// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfCaveSpawnActor.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/Characters/Enemies/Enemy_wolf.h"

AWolfCaveSpawnActor::AWolfCaveSpawnActor() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/World/Pirate_Town_Set/Meshes/Stone_Mine.Stone_Mine'"));
	if (Mesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(Mesh.Object);
		//StaticMeshComponent->SetWorldScale3D(FVector(6,6,4));
	}
	TerrainExtent = FVector(300);
	SpawnComponent->ActorToSpawn = AEnemy_Wolf::StaticClass();
	SpawnComponent->MaxSpawnCount = FMath::RandRange(3, 5);
}