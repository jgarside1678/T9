// Fill out your copyright notice in the Description page of Project Settings.
#include "Building_Townhall.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/Characters/Alliance/Alliance_Lumberjack.h"
#include "TimerManager.h"


ABuilding_Townhall::ABuilding_Townhall(const FObjectInitializer& ObjectInitializer) {

	OutlineColour = 1;
	GridLength = FVector2D(9);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/Assets/Fantasy_Village/meshes/buildings/SM_house_b.SM_house_b'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh1(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1B.Tower_Base1B'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh2(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1C.Tower_Base1C'"));
	//static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationMont(TEXT("AnimSequence'/Game/AI/Alliance/StylizedHumanMale/Animations/Standing_1H_Magic_Attack_01_mixamo_com.Standing_1H_Magic_Attack_01_mixamo_com'"));
	if (BaseMesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(BaseMesh.Object);
		//StaticMeshComponent->SetWorldScale3D(FVector(6,6,4));
	}

	//{Level, FBuildingUpgrades{XP, Maxhealth, FBuildingCosts{Gold, Wood, Stone, Food}, Damage, AttackSpeed, FBuildingProduction{Gold, Wood, Stone, Food}}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 100, 1000.0f, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{0,0, 2}, FBuildingProduction{100} });
	Upgrades.Add(2, FBuildingUpgrades{ 250.0f, 250, 5000.0f, FBuildingCosts{250, 20, 20, 20}, FBuildingAttack{0,0, 5}, FBuildingProduction{200} });
	Upgrades.Add(3, FBuildingUpgrades{ 500.0f, 500, 10000.0f, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{0,0, 6}, FBuildingProduction{300} });
	BuildingDetectionRange = Upgrades[Level].Attack.AttackRangeMultipler;
	BuildingName = "Town Hall";
	SpawnComponent = CreateDefaultSubobject<UBuildingSpawnComponent>(TEXT("Spawn Component"));
    SpawnComponent->ActorToSpawn = AAlliance_Lumberjack::StaticClass();
	SpawnComponent->SpawnMethod = PointSpawn;
	SpawnComponent->SpawnLocation = FVector(440, 0, 200);
	SpawnComponent->MaxSpawnRange = 500;
}

void ABuilding_Townhall::BeginPlay()
{

	Super::BeginPlay();
	if (SpawnComponent)SpawnComponent->Init();
}

void ABuilding_Townhall::Upgrade()
{
	Super::Upgrade();
}

void ABuilding_Townhall::ResourceInit() {
	Super::ResourceInit();
}
