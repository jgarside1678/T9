// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSpawnComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "T9/Characters/CharacterActor.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "T9/Actors/Items/ItemActor.h"
#include "T9/Actors/Components/InventoryComponent.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include <Runtime\Engine\Classes\Engine\World.h>
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"


UBuildingSpawnComponent::UBuildingSpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	InventoryComponent->SetCapacity(3);
	InventoryComponent->OnInventoryUpdate.AddDynamic(this, &UBuildingSpawnComponent::UpdateCharactersInventory);
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
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = SpawnParamCollision;
		ACharacterActor* SpawnedActorRef = GetWorld()->SpawnActor<ACharacterActor>(ActorToSpawn, SpawnLocation, FRotator(0.0f,0.0f,0.0f), SpawnParams);
		ActorsSpawned.Add(SpawnedActorRef);
		if (SpawnedActorRef) {
			CurrentSpawnCount++;
			UpdateCharactersInventory();
			SpawnedActorRef->InitalLocation = SpawnLocation;
			if(OwningBuilding)	SpawnedActorRef->SpawnInit(MyOwner, OwningBuilding->GetLevel());
			else if(PS) SpawnedActorRef->SpawnInit(MyOwner, PS->GetLevel());
			else SpawnedActorRef->SpawnInit(MyOwner);
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
		else if (SpawnMethod == PointSpawn) {
			SpawnLocation += MyOwner->GetActorLocation();
		}
		else {

		}
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
	CurrentSpawnCount = 0;
	MyOwner->GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
}

UInventoryComponent* UBuildingSpawnComponent::GetInventoryComponent()
{
	return InventoryComponent;
}

void UBuildingSpawnComponent::UpdateCharactersInventory()
{
	if (InventoryComponent) {
		TArray<FSlot> Slots = InventoryComponent->GetItems();
		for (int z = 0; z < ActorsSpawned.Num(); z++) {
			if (ActorsSpawned[z]) {
				ActorsSpawned[z]->ResetEquipment();
				for (int x = 0; x < Slots.Num(); x++) {
					if (Slots[x].Item) {
						switch (Slots[x].Item->GetItemSocket()) {
						case MainHand:
							ActorsSpawned[z]->AddMainHand(Slots[x].Item);
							break;
						default:
							break;
						}
					}
				}
			}
		}
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
		MyOwner->GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &UBuildingSpawnComponent::AutoRespawn, SpawnTime, false, SpawnTime);
	}
}


void UBuildingSpawnComponent::UpdateSpawnedCharacters() {
	if (OwningBuilding) {
		for (int x = 0; x < ActorsSpawned.Num(); x++) {
			if (ActorsSpawned[x] != nullptr) {
				ActorsSpawned[x]->SetLevel(OwningBuilding->GetLevel());
			}
		}
	}
}