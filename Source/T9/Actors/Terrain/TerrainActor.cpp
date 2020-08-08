// Fill out your copyright notice in the Description page of Project Settings.
#include "TerrainActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATerrainActor::ATerrainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	TerrainCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	TerrainCollider->SetupAttachment(RootComponent);
	TerrainCollider->SetCollisionProfileName("Trigger");


}

// Called when the game starts or when spawned
void ATerrainActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

