// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSpawnComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "CharacterActor.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "BuildingActor.h"
#include <Runtime\Engine\Classes\Engine\World.h>
#include "MainPlayerController.h"
#include "MainPlayerState.h"


// Sets default values for this component's properties
UBuildingSpawnComponent::UBuildingSpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}



// Called when the game starts
void UBuildingSpawnComponent::BeginPlay()

{
	Super::BeginPlay();
	MyOwner = (AActor*)GetOwner();
	OwningBuilding = Cast<ABuildingActor>(MyOwner);
	Init();
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;

}


// Called every frame
void UBuildingSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



AActor* UBuildingSpawnComponent::Spawn() {
	if (CurrentSpawnCount < MaxSpawnCount) {
		CurrentSpawnCount++;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = SpawnParamCollision;
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator(0.0f,0.0f,0.0f), SpawnParams);
		ACharacterActor* SpawnedCharacter = (ACharacterActor*)SpawnedActorRef;
		ActorsSpawned.Add(SpawnedActorRef);
		if (SpawnedCharacter) {
			if(OwningBuilding)	SpawnedCharacter->SpawnInit(MyOwner, OwningBuilding->GetLevel());
			else if(PS) SpawnedCharacter->SpawnInit(MyOwner, PS->GetLevel());
			else SpawnedCharacter->SpawnInit(MyOwner);
		}
		if (SpawnedActorRef) return SpawnedActorRef;
	}
	return nullptr;
}

void UBuildingSpawnComponent::Init()
{
	if (ActorToSpawn && MyOwner && MaxSpawnCount > CurrentSpawnCount) {
		AActor* NewSpawn = nullptr;
		if (SpawnMethod == SurroundingBuilding && OwningBuilding) {
			BoxExtent = OwningBuilding->BuildingExtent;
			Origin = MyOwner->GetActorLocation();
			if (MaxSpawnRange < BoxExtent.X) {
				MaxSpawnRange = BoxExtent.X + 200;
			}
			RandomSpawnLocation();
			SpawnLocation = FVector(Origin.X + XAxis, Origin.Y + YAxis, 10.0f);
		}
		else SpawnLocation += MyOwner->GetActorLocation();
		AutoRespawn();
	}
}

void UBuildingSpawnComponent::RandomSpawnLocation()
{
	float random = RandomFloat(0, 1);
	if (random > 0.5) {
		XAxis = RandomFloat(MaxSpawnRange, (MaxSpawnRange * -1));
		if ((XAxis < BoxExtent.X) && (XAxis > (BoxExtent.X * -1))) {
			if (random < 0.75) YAxis = RandomFloat(BoxExtent.Y, MaxSpawnRange);
			else YAxis = RandomFloat((BoxExtent.Y * -1), (MaxSpawnRange * -1));
		}
		else YAxis = RandomFloat(MaxSpawnRange, (MaxSpawnRange * -1));
	}
	else {
		YAxis = RandomFloat(MaxSpawnRange, (MaxSpawnRange * -1));
		if ((YAxis < BoxExtent.Y) && (YAxis > (BoxExtent.Y * -1))) {
			if (random < 0.25) XAxis = RandomFloat(BoxExtent.Y, MaxSpawnRange);
			else XAxis = RandomFloat((BoxExtent.Y * -1), (MaxSpawnRange * -1));
		}
		else XAxis = RandomFloat(MaxSpawnRange, (MaxSpawnRange * -1));
	}
}

float UBuildingSpawnComponent::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void UBuildingSpawnComponent::KillAll() {
	for (int x = 0; x < ActorsSpawned.Num(); x++) {
		if (ActorsSpawned[x] != nullptr) ActorsSpawned[x]->Destroy();
	}
}

void UBuildingSpawnComponent::AutoRespawn() {
	if (CurrentSpawnCount < MaxSpawnCount) {
		AutoSpawning = true;
		Spawn();
		MyOwner->GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &UBuildingSpawnComponent::AutoRespawn, SpawnTime, false, SpawnTime);
	}
	else AutoSpawning = false;
}

void UBuildingSpawnComponent::Respawn() {
	if (!AutoSpawning) {
		UE_LOG(LogTemp, Warning, TEXT("2 2"));
		MyOwner->GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &UBuildingSpawnComponent::AutoRespawn, SpawnTime, false, SpawnTime);
	}
	UE_LOG(LogTemp, Warning, TEXT("1 1"));
}


void UBuildingSpawnComponent::UpdateSpawnedCharacters() {
	if (OwningBuilding) {
		ACharacterActor* Character;
		for (int x = 0; x < ActorsSpawned.Num(); x++) {
			if (ActorsSpawned[x] != nullptr) {
				Character = Cast<ACharacterActor>(ActorsSpawned[x]);
				Character->SetLevel(OwningBuilding->GetLevel());
			}
		}
	}
}