// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Wood.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AResource_Wood::AResource_Wood() {
	ResourceType = Wood;
	CollectionDistance = FVector(50);
	BoxExtentMultiplier = FVector(10);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tier1Mesh(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Props/trees/Fol_Tree_06.Fol_Tree_06'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tier2Mesh(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Props/trees/Fol_Tree_07.Fol_Tree_07'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tier3Mesh(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Props/trees/Fol_Tree_09.Fol_Tree_09'"));
	ResourceTiers.Add(Tier1, FResourceTierStats{ "Chestnut Oak Forest", Tier1Mesh.Object,nullptr, 1});
	ResourceTiers.Add(Tier2, FResourceTierStats{ "Scarlet Oak Forest", Tier2Mesh.Object, nullptr, 1.25});
	ResourceTiers.Add(Tier3, FResourceTierStats{ "Pink Cherry Forest",Tier3Mesh.Object, nullptr, 1.5});
	if (Tier1Mesh.Succeeded()) StaticMeshComponent->SetStaticMesh(Tier1Mesh.Object);
	BoxCollider->SetBoxExtent(BoxExtentMultiplier * 100);

	TArray<FVector2D> Sections;
	Sections.Add(FVector2D(FMath::RandRange(-900, -300), FMath::RandRange(-900, -300)));
	Sections.Add(FVector2D(FMath::RandRange(-300, 300), FMath::RandRange(-900, -300)));
	Sections.Add(FVector2D(FMath::RandRange(300, 900), FMath::RandRange(-900, -300)));

	Sections.Add(FVector2D(FMath::RandRange(-900, -300), FMath::RandRange(-300, 300)));
	Sections.Add(FVector2D(FMath::RandRange(-300, 300), FMath::RandRange(-300, 300)));
	Sections.Add(FVector2D(FMath::RandRange(300, 900), FMath::RandRange(-300, 300)));

	Sections.Add(FVector2D(FMath::RandRange(-900, -300), FMath::RandRange(300, 900)));
	Sections.Add(FVector2D(FMath::RandRange(-300, 300), FMath::RandRange(300, 900)));
	Sections.Add(FVector2D(FMath::RandRange(300, 900), FMath::RandRange(300, 900)));

	for (int x = 0; x < Sections.Num(); x++) {
		int Chance = FMath::RandRange(0, 1);
		if (Chance == 1 || (x == Sections.Num() - 1 && StaticMeshComponent->InstanceBodies.Num() == 0)) {
			StaticMeshComponent->AddInstance(FTransform(FRotator(0, FMath::RandRange(0, 270), 0), FVector(Sections[x].X, Sections[x].Y, 0), FVector(FMath::RandRange(1, 2.3))));
		}
	}
}
