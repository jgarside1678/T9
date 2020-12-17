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
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	if (StaticMeshComponent) {
		StaticMeshComponent->SetCustomDepthStencilValue(1);
		StaticMeshComponent->SetRenderCustomDepth(false);
		StaticMeshComponent->SetGenerateOverlapEvents(true);
	}

	TerrainCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	TerrainCollider->SetupAttachment(RootComponent);
	TerrainCollider->SetCollisionProfileName("Trigger");


}

// Called when the game starts or when spawned
void ATerrainActor::BeginPlay()
{
	TerrainCollider->SetBoxExtent(StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent);
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

