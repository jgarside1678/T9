// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceActor.h"
#include "Components/BoxComponent.h"
#include "T9/MainPlayerController.h"
#include "DrawDebugHelpers.h"
#include "T9/MainPlayerState.h"
#include "T9/Actors/GameGridActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "T9/Widgets/ResourceQuickSelect.h"

// Sets default values
AResourceActor::AResourceActor() :	ResourceQuickSelectComponent(CreateDefaultSubobject<UWidgetComponent>(TEXT("Resource Quick Select")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetCollisionProfileName("Trigger");
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	RootComponent = BoxCollider;
	StaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	GridSpace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridSpace"));
	GridSpace->SetupAttachment(RootComponent);
	GridSpace->SetCollisionProfileName("NoCollision");
	if (GridSpace) {
		GridSpace->SetCustomDepthStencilValue(OutlineColour);
		GridSpace->SetRenderCustomDepth(true);
		GridSpace->SetVisibility(false);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Plane(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> PlaneColour(TEXT("MaterialInstanceConstant'/Game/Materials/Grid/GridSpace_Resources.GridSpace_Resources'"));
		if (Plane.Succeeded()) {
			GridSpace->SetStaticMesh(Plane.Object);
			GridSpace->SetMaterial(0, PlaneColour.Object);
		}
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ResourceQuickSelectWidget(TEXT("WidgetBlueprint'/Game/UI/ResourceQuickSelect_BP.ResourceQuickSelect_BP_C'"));
	if (ResourceQuickSelectWidget.Succeeded()) ResourceQuickSelectClass = ResourceQuickSelectWidget.Class;

	if (ResourceQuickSelectComponent) {
		ResourceQuickSelectComponent->SetupAttachment(RootComponent);
		ResourceQuickSelectComponent->SetWidgetSpace(EWidgetSpace::Screen);
		ResourceQuickSelectComponent->SetRelativeLocation(FVector(0.0f, 0.0f, ResourceSelectHeight));
		ResourceQuickSelectComponent->SetVisibility(false);
		if (ResourceQuickSelectClass != nullptr) ResourceQuickSelectComponent->SetWidgetClass(ResourceQuickSelectClass);
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
	ResourceQuickSelect = Cast<UResourceQuickSelect>(ResourceQuickSelectComponent->GetUserWidgetObject());
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
	FVector ClosestInstanceBounds;
	FVector MeshBounds = StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent;;
	float ClosestDistance = 1000000;
	for (int x = 0; x < StaticMeshComponent->GetInstanceCount(); x++) {
		StaticMeshComponent->GetInstanceTransform(x, ComponentTransform, true);
		float Distance = (Location - ComponentTransform.GetLocation()).Size();
		if (Distance < ClosestDistance) {
			ClosestDistance = Distance;
			ClosestInstanceBounds = MeshBounds * ComponentTransform.GetScale3D();
			ClosestMeshLocation = ComponentTransform.GetLocation();
		}
	}
	ClosestMeshBounds = ClosestInstanceBounds;
	//ClosestMeshBounds = FVector(CollectionDistance.X * ClosestTransform.GetScale3D().X, CollectionDistance.Y * ClosestTransform.GetScale3D().Y, CollectionDistance.Z * ClosestTransform.GetScale3D().Z);
	DrawDebugBox(GetWorld(), ClosestMeshLocation, ClosestInstanceBounds, FColor::Red, true, -1, 0, 10);
}

void AResourceActor::GetClosestSpawnedCharacter(FVector Location, AResourceCharacter*& ClosestCharacter)
{
	ACharacter* Closest = nullptr;
	FVector ClosestOrigin;
	float ClosestDistance = 1000000;
	for (int x = 0; x < ResourceSpawns.Num(); x++) {
		if (ResourceSpawns[x]) {
			FVector CharacterLocation = ResourceSpawns[x]->GetActorLocation();
			float Distance = (Location - CharacterLocation).Size();
			if (Distance < ClosestDistance) {
				ClosestDistance = Distance;
				Closest = ResourceSpawns[x];
			}
		}
	}
	ClosestCharacter = Cast<AResourceCharacter>(Closest);
}


void AResourceActor::SetSelected()
{
	StaticMeshComponent->SetRenderCustomDepth(true);
	for (int x = 0; x < ResourceSpawns.Num(); x++) ResourceSpawns[x]->GetMesh()->SetRenderCustomDepth(true);
	if (ResourceQuickSelectComponent) ResourceQuickSelectComponent->SetVisibility(true);
}

void AResourceActor::SetUnSelected()
{
	StaticMeshComponent->SetRenderCustomDepth(false);
	for (int x = 0; x < ResourceSpawns.Num(); x++) ResourceSpawns[x]->GetMesh()->SetRenderCustomDepth(false);
	if (ResourceQuickSelectComponent) ResourceQuickSelectComponent->SetVisibility(false);

}

FString AResourceActor::GetName()
{
	return Name;
}

void AResourceActor::ResourceInit(AGameGridActor* Grid, TEnumAsByte<Tiers> StartingResourceTier)
{
	FVector Location = GetActorLocation() - (BoxExtentMultiplier * 100);
	Grid->SetTilesActive(Location, BoxExtentMultiplier.X*2, BoxExtentMultiplier.Y*2);
	GridSpace->SetWorldScale3D(FVector(BoxExtentMultiplier.X * 2, BoxExtentMultiplier.Y * 2, 1));
	GridSpace->SetRelativeLocation(FVector(0, 0, 1));
	if (ResourceTiers.Contains(StartingResourceTier)) {
		Tier = StartingResourceTier;
		Name = ResourceTiers[StartingResourceTier].Name;
		if(ResourceTiers[StartingResourceTier].ResourceMesh) StaticMeshComponent->SetStaticMesh(ResourceTiers[StartingResourceTier].ResourceMesh);
	}
	if (ResourceQuickSelect)	ResourceQuickSelect->Init(this);
}

