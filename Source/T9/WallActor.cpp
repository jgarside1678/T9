// Fill out your copyright notice in the Description page of Project Settings.
#include "WallActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWallActor::AWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced StaticMesh"));
	RootComponent = InstancedStaticMesh;
	BuildingCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BuildingCollider->SetCollisionProfileName("Trigger");
	BuildingCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

