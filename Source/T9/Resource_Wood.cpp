// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Wood.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AResource_Wood::AResource_Wood() {
	ResourceType = Wood;
	Name = "Oak Forest";
	CollectionDistance = FVector(50);
	BoxExtentMultiplier = FVector(10);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Props/trees/Fol_Tree_07.Fol_Tree_07'"));
	if (Mesh.Succeeded()) {
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

		StaticMeshComponent->SetStaticMesh(Mesh.Object);


		for (int x = 0; x < Sections.Num(); x++) {
			int Chance = FMath::RandRange(0, 1);
			if (Chance == 1 || (x == Sections.Num() - 1 && StaticMeshComponent->InstanceBodies.Num() == 0)) {
				StaticMeshComponent->AddInstance(FTransform(FRotator(0, FMath::RandRange(0, 270), 0), FVector(Sections[x].X, Sections[x].Y, 0), FVector(FMath::RandRange(1, 2.3))));
			}
		}
	}
	BoxCollider->SetBoxExtent(BoxExtentMultiplier * 100);


}



//AResource_Wood::AResource_Wood() {
//	ResourceType = Wood;
//	Name = "Oak Forest";
//	CollectionDistance = FVector(50);
//	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Props/trees/Fol_Tree_07.Fol_Tree_07'"));
//	if (Mesh.Succeeded()) {
//		StaticMeshComponent->SetStaticMesh(Mesh.Object);
//		StaticMeshComponent->AddInstance(FTransform(FRotator(0), FVector(0), FVector(1)));
//		StaticMeshComponent->AddInstance(FTransform(FRotator(0, 50, 0), FVector(400, 500, 0), FVector(2)));
//		StaticMeshComponent->AddInstance(FTransform(FRotator(0), FVector(550, -390, 0), FVector(1.2, 1.2, 1.3)));
//
//		StaticMeshComponent->AddInstance(FTransform(FRotator(0, FMath::RandRange(0, 100), 0), FVector(FMath::RandRange(-400, 700), FMath::RandRange(-500, 100), 0), FVector(FMath::RandRange(1, 3))));
//	}
//	BoxCollider->SetBoxExtent(FVector(1000));
//
//
//}