// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectableTerrainActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASelectableTerrainActor::ASelectableTerrainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelectableTerrainActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectableTerrainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectableTerrainActor::SetSelected()
{
	StaticMeshComponent->SetRenderCustomDepth(true);
}

void ASelectableTerrainActor::SetUnSelected()
{
	StaticMeshComponent->SetRenderCustomDepth(false);
}

FString ASelectableTerrainActor::GetName()
{
	return TerrainName;
}

int ASelectableTerrainActor::GetLevel()
{
	return 1;
}

