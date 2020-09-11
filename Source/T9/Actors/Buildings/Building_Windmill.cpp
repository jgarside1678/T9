// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_Windmill.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "T9/Actors/Components/InventoryComponent.h"


ABuilding_Windmill::ABuilding_Windmill(const FObjectInitializer& ObjectInitializer) {
	HealthBarHeight = 1400;
	AdditionalStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Windmill Blades"));
	AdditionalStaticMeshComponent->SetupAttachment(StaticMeshComponent);
	AdditionalStaticMeshComponent->SetCanEverAffectNavigation(false);
	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation"));
	RotationComp->SetUpdatedComponent(AdditionalStaticMeshComponent);
	RotationComp->RotationRate = FRotator(7, 0, 0);
	AdditionalStaticMeshComponent->SetRelativeLocation(FVector(0, 400, 1065));
	OutlineColour = 1;
	GridLength = FVector2D(9, 8);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/Assets/Pirate_Town_Set/Meshes/Windmill.Windmill'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WindmillBlades(TEXT("StaticMesh'/Game/Assets/Pirate_Town_Set/Meshes/Windmill_Fan.Windmill_Fan'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageLevel1(TEXT("Texture2D'/Game/Assets/UI/WindmillImage.WindmillImage'"));

	if (BaseMesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(BaseMesh.Object);
	}
	if (WindmillBlades.Succeeded()) {
		AdditionalStaticMeshComponent->SetStaticMesh(WindmillBlades.Object);
	}

	//{Level, FBuildingUpgrades{XP, PowerRating, Maxhealth, Defence, FBuildingCosts{Gold, Wood, Stone, Food}, FBuildingAttack{Damage, AttackSpeed, AttackRange}, FBuildingProduction{Gold, Wood, Stone, Food}}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 100, 1000.0f, 10.0f, ImageLevel1.Object, FBuildingCosts{100, 100, 100, 0}, FBuildingAttack{0,0, 2}, FBuildingProduction{0,0,0,100} });
	Upgrades.Add(2, FBuildingUpgrades{ 250.0f, 250, 2000.0f, 100.0f, ImageLevel1.Object, FBuildingCosts{2500, 2000, 2000, 0}, FBuildingAttack{0,0, 5}, FBuildingProduction{0,0,0,200} });
	Upgrades.Add(3, FBuildingUpgrades{ 500.0f, 350, 4000.0f, 250.0f, ImageLevel1.Object, FBuildingCosts{5000, 5000, 5000, 0}, FBuildingAttack{0,0, 6}, FBuildingProduction{0,0,0,300} });
	MeshDisplacement->SetRelativeLocation(FVector(-150, 0,0));
	BuildingName = "Windmill";
}

void ABuilding_Windmill::BeginPlay()
{

	Super::BeginPlay();
}

void ABuilding_Windmill::Upgrade()
{
	Super::Upgrade();
}

void ABuilding_Windmill::ResourceInit() {
	Super::ResourceInit();
}

