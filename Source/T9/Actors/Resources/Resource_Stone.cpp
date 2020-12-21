// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Stone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AResource_Stone::AResource_Stone() {
	ResourceType = Stone;
	CollectionDistance = FVector(50);
	BoxExtentMultiplier = FVector(6);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tier1Mesh(TEXT("StaticMesh'/Game/World/Fantasy_Village/meshes/stones/SM_stone_a.SM_stone_a'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tier2Mesh(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Props/stones/Stone_Block2.Stone_Block2'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tier3Mesh(TEXT("StaticMesh'/Game/World/Stylized_Vegetation/Geometry/Rocks/Rocks_Large/SM_Rock_Large_01.SM_Rock_Large_01'"));
	ResourceTiers.Add(Tier1, FResourceTierStats{ "Stone Quarry", Tier1Mesh.Object, nullptr, 1 });
	ResourceTiers.Add(Tier2, FResourceTierStats{ "Basalt Quarry", Tier2Mesh.Object, nullptr, 1.25 });
	ResourceTiers.Add(Tier3, FResourceTierStats{ "Granite Quarry",Tier3Mesh.Object, nullptr, 1.5 });
	if (Tier1Mesh.Succeeded()) StaticMeshComponent->SetStaticMesh(Tier1Mesh.Object);
	BoxCollider->SetBoxExtent(BoxExtentMultiplier * 100);

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


	for (int x = 0; x < Sections.Num(); x++) {
		int Chance = FMath::RandRange(0, 1);
		if (Chance == 1 || (x == Sections.Num() - 1 && StaticMeshComponent->InstanceBodies.Num() == 0)) {
			StaticMeshComponent->AddInstance(FTransform(FRotator(0, FMath::RandRange(0, 270), 0), FVector(Sections[x].X, Sections[x].Y, 0), FVector(FMath::RandRange(1, 4))));
		}
	}


}
