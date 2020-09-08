// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Food.h"
#include "Components/BoxComponent.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
	if (ResourceTiers.Contains(Tier)) Name = ResourceTiers[Tier].Name;
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

void AResource_Food::KillAll() {
	for (int x = 0; x < ResourceSpawns.Num(); x++) {
		if (ResourceSpawns[x] != nullptr) ResourceSpawns[x]->Destroy();
	}
	CurrentSpawnCount = 0;
}


void AResource_Food::AutoRespawn() {
	if (CurrentSpawnCount < MaxSpawnCount) {
		AutoSpawning = true;
		Spawn();
		GetWorldTimerManager().SetTimer(ResourceSpawnTimerHandle, this, &AResource_Food::AutoRespawn, SpawnTime, false, SpawnTime);
	}
	else AutoSpawning = false;
}

void AResource_Food::Respawn() {
	if (!AutoSpawning) {
		GetWorldTimerManager().SetTimer(ResourceSpawnTimerHandle, this, &AResource_Food::AutoRespawn, SpawnTime, false, SpawnTime);
	}
}

ACharacter* AResource_Food::Spawn() {
	if (CurrentSpawnCount < MaxSpawnCount) {
		FActorSpawnParameters SpawnParams;
		FVector SpawnLocation;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		AResourceCharacter* SpawnedActorRef = nullptr;
		while (!SpawnedActorRef) {
			SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), BoxCollider->GetScaledBoxExtent());
			SpawnedActorRef = GetWorld()->SpawnActor<AResourceCharacter>(ResourceTiers[Tier].ResourceSpawnCharacter, FVector(SpawnLocation.X, SpawnLocation.Y, 100), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		}
		ResourceSpawns.Add(SpawnedActorRef);
		if (SpawnedActorRef) {
			CurrentSpawnCount++;
			SpawnedActorRef->Init(this, SpawnLocation);
		}
		if (SpawnedActorRef) return SpawnedActorRef;
	}
	return nullptr;
}

