// Fill out your copyright notice in the Description page of Project Settings.


#include "StonePortalSpawnActor.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/Characters/Enemies/Enemy_Lava_Elemental.h"

AStonePortalSpawnActor::AStonePortalSpawnActor() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Props/stones/Stone_Jar2B.Stone_Jar2B'"));
	if (Mesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(Mesh.Object);
		StaticMeshComponent->SetWorldScale3D(FVector(8));
		StaticMeshComponent->SetCollisionProfileName("NoCollision");
		StaticMeshComponent->SetCanEverAffectNavigation(false);
	}
	SpawnComponent->ActorToSpawn = AEnemy_Lava_Elemental::StaticClass();
	SpawnComponent->MaxSpawnCount = 1;
}
