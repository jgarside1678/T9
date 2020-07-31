// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceActor.h"
#include "Components/BoxComponent.h"
#include "MainPlayerController.h"
#include "DrawDebugHelpers.h"
#include "MainPlayerState.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AResourceActor::AResourceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = StaticMeshComponent;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void AResourceActor::BeginPlay()
{
	Super::BeginPlay();
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	if (PS) {
		PS->SpawnedResources.Add(this);
	}
}

// Called every frame
void AResourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Sets Closest Instance Location for AI to walk to
void AResourceActor::GetClosestStaticMesh(FVector Location, FVector& ClosestMeshLocation, FVector& ClosestMeshBounds)
{
	FTransform ComponentTransform;
	float ClosestDistance = 1000000;
	for (int x = 0; x < StaticMeshComponent->GetInstanceCount(); x++) {
		StaticMeshComponent->GetInstanceTransform(x, ComponentTransform, true);
		float Distance = (Location - ComponentTransform.GetLocation()).Size();
		if (Distance < ClosestDistance) {
			ClosestDistance = Distance;
			ClosestMeshLocation = ComponentTransform.GetLocation();
		}
	}
	ClosestMeshBounds = FVector(CollectionDistance.X * ComponentTransform.GetScale3D().X, CollectionDistance.Y * ComponentTransform.GetScale3D().Y, CollectionDistance.Z * ComponentTransform.GetScale3D().Z);
	//DrawDebugBox(GetWorld(), ComponentLocation, FVector(CollectionDistance.X * MeshScale.X, CollectionDistance.Y * MeshScale.Y, CollectionDistance.Z * MeshScale.Z), FQuat(GetActorRotation()), FColor::Green, true, -1, 0, 10);
}

void AResourceActor::SetSelected()
{
	StaticMeshComponent->SetRenderCustomDepth(true);
}

void AResourceActor::SetUnSelected()
{
	StaticMeshComponent->SetRenderCustomDepth(false);
}

FString AResourceActor::GetName()
{
	return Name;
}

