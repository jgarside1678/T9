// Fill out your copyright notice in the Description page of Project Settings.
#include "Building_Townhall.h"
#include "BuildingSpawnComponent.h"
#include "Alliance_Lumberjack.h"
#include "TimerManager.h"


ABuilding_Townhall::ABuilding_Townhall(const FObjectInitializer& ObjectInitializer) {

	OutlineColour = 1;
	//{Level, FBuildingUpgrades{XP, Maxhealth, FBuildingCosts{Gold, Wood, Stone, Food}, Damage, AttackSpeed, FBuildingProduction{Gold, Wood, Stone, Food}}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 1000.0f, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{0,0, 2}, FBuildingProduction{100} });
	Upgrades.Add(2, FBuildingUpgrades{ 250.0f, 5000.0f, FBuildingCosts{250, 20, 20, 20}, FBuildingAttack{0,0, 5}, FBuildingProduction{200} });
	Upgrades.Add(3, FBuildingUpgrades{ 500.0f, 10000.0f, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{0,0, 6}, FBuildingProduction{300} });
	BuildingDetectionRange = Upgrades[Level].Attack.AttackRangeMultipler;
	BuildingName = "Town Hall";
	SpawnComponent = CreateDefaultSubobject<UBuildingSpawnComponent>(TEXT("Spawn Component"));
    SpawnComponent->ActorToSpawn = AAlliance_Lumberjack::StaticClass();
	SpawnComponent->MaxSpawnRange = 500;
}

void ABuilding_Townhall::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	BuildingExtent = BuildingExtent * 2;
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
