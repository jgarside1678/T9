// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowPortalSpawnActor.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/Characters/Enemies/Enemy_Forest_Spider.h"

ASnowPortalSpawnActor::ASnowPortalSpawnActor() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/snowy_landscape/mesh/ruins/SM_sacrifices_plate.SM_sacrifices_plate'"));
	if (Mesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(Mesh.Object);
		StaticMeshComponent->SetWorldScale3D(FVector(1));
		StaticMeshComponent->SetCollisionProfileName("NoCollision");
		StaticMeshComponent->SetCanEverAffectNavigation(false);
	}
	SpawnComponent->ActorToSpawn = AEnemy_Forest_Spider::StaticClass();
	SpawnComponent->MaxSpawnCount = 3;
}
