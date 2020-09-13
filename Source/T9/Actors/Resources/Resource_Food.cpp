// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Food.h"
#include "Components/BoxComponent.h"
#include "T9/Actors/Resources/ResourceCharacter_Boar.h"
#include "T9/Actors/Resources/ResourceCharacter_Goat.h"
#include "T9/Actors/Resources/ResourceCharacter_Bear.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "Components/StaticMeshComponent.h"

AResource_Food::AResource_Food() {
	ResourceType = Food;
	CollectionDistance = FVector(50);
	BoxExtentMultiplier = FVector(8);
	ResourceTiers.Add(Tier1, FResourceTierStats{ "Wild Goats", nullptr, AResourceCharacter_Goat::StaticClass(), 1 });
	ResourceTiers.Add(Tier2, FResourceTierStats{ "Wild Boars", nullptr, AResourceCharacter_Boar::StaticClass(), 1.25 });
	ResourceTiers.Add(Tier3, FResourceTierStats{ "Wild Bears",nullptr, AResourceCharacter_Bear::StaticClass(), 1.5 });
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

	MaxSpawnCount = FMath::RandRange(3,5);


}

void AResource_Food::ResourceInit(class AGameGridActor* Grid, TEnumAsByte<Tiers> StartingResourceTier)
{
	Super::ResourceInit(Grid, StartingResourceTier);
	AutoRespawn();
}
