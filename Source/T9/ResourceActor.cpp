// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceActor.h"
#include "Components/BoxComponent.h"
#include "MainPlayerController.h"
#include "DrawDebugHelpers.h"
#include "MainPlayerState.h"
#include "GameGridActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AResourceActor::AResourceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetCollisionProfileName("Trigger");
	RootComponent = BoxCollider;
	StaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	GridSpace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridSpace"));
	GridSpace->SetupAttachment(RootComponent);
	if (GridSpace) {
		GridSpace->SetCustomDepthStencilValue(OutlineColour);
		GridSpace->SetRenderCustomDepth(true);
		GridSpace->SetVisibility(false);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Plane(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> PlaneColour(TEXT("MaterialInstanceConstant'/Game/Materials/Grid/GridColour_Resources.GridColour_Resources'"));
		if (Plane.Succeeded()) {
			GridSpace->SetStaticMesh(Plane.Object);
			GridSpace->SetMaterial(0, PlaneColour.Object);
		}
	}
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

void AResourceActor::ResourceInit(AGameGridActor* Grid)
{
	FVector Location = GetActorLocation() - (BoxExtentMultiplier * 100);
	Grid->SetTilesActive(Location, BoxExtentMultiplier.X*2, BoxExtentMultiplier.Y*2);
	GridSpace->SetWorldScale3D(FVector(BoxExtentMultiplier.X * 2, BoxExtentMultiplier.Y * 2, 1));
	GridSpace->SetRelativeLocation(FVector(0, 0, 1));
}

