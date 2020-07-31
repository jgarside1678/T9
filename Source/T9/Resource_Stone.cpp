// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Stone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AResource_Stone::AResource_Stone() {
	ResourceType = Stone;
	Name = "Stone Quarry";
	CollectionDistance = FVector(50);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/Fantasy_Village/meshes/stones/SM_stone_a.SM_stone_a'"));
	if (Mesh.Succeeded()) {
		TArray<FVector2D> Sections;
		Sections.Add(FVector2D(FMath::RandRange(-300, -100), FMath::RandRange(-300, -100)));
		Sections.Add(FVector2D(FMath::RandRange(-100, 100), FMath::RandRange(-300, -100)));
		Sections.Add(FVector2D(FMath::RandRange(100, 300), FMath::RandRange(-300, -100)));

		Sections.Add(FVector2D(FMath::RandRange(-300, -100), FMath::RandRange(-100, 100)));
		Sections.Add(FVector2D(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100)));
		Sections.Add(FVector2D(FMath::RandRange(100, 300), FMath::RandRange(-100, 100)));

		Sections.Add(FVector2D(FMath::RandRange(-300, -100), FMath::RandRange(300, 100)));
		Sections.Add(FVector2D(FMath::RandRange(-100, 100), FMath::RandRange(300, 100)));
		Sections.Add(FVector2D(FMath::RandRange(100, 300), FMath::RandRange(300, 100)));
		StaticMeshComponent->SetStaticMesh(Mesh.Object);


		for (int x = 0; x < Sections.Num(); x++) {
			int Chance = FMath::RandRange(0, 1);
			if (Chance == 1 || (x == Sections.Num() - 1 && StaticMeshComponent->InstanceBodies.Num() == 0)) {
				StaticMeshComponent->AddInstance(FTransform(FRotator(0, FMath::RandRange(0, 270), 0), FVector(Sections[x].X, Sections[x].Y, 0), FVector(FMath::RandRange(1, 4))));
			}
		}
	}
	BoxCollider->SetBoxExtent(FVector(300));


}
