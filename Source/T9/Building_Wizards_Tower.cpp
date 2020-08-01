// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_Wizards_Tower.h"
#include "MainPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainPlayerState.h"
#include "Alliance_Wizard.h"
#include "Projectile_Arrow.h"

ABuilding_Wizards_Tower::ABuilding_Wizards_Tower(const FObjectInitializer& ObjectInitializer) {
	// XP / Cost / Maxhealth / Damage

	Projectile = AProjectile_Arrow::StaticClass();
	ProjectileSpawn->SetRelativeLocation(FVector(0,0,0.0f));
	ProjectileDelay = 0.5f;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1A.Tower_Base1A'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh1(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1B.Tower_Base1B'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh2(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1C.Tower_Base1C'"));
	if (BaseMesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(BaseMesh.Object);
	}
	//{Level, FBuildingUpgrades{XP, FBuildingCosts{Gold, Wood, Stone, Food}, Maxhealth, FBuildingAttack{Damage, AttackSpeed, AttackRange}, FBuildingProduction{Gold, Wood, Stone, Food}}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 1000.0f, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{40, 3, 10}, FBuildingProduction{} });
	Upgrades.Add(2, FBuildingUpgrades{ 250.0f, 5000.0f, FBuildingCosts{250, 20, 20, 20}, FBuildingAttack{60, 3, 10}, FBuildingProduction{}, BaseMesh1.Object});
	Upgrades.Add(3, FBuildingUpgrades{ 500.0f, 10000.0f, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{100, 3, 10}, FBuildingProduction{}, BaseMesh2.Object });
	BuildingDetectionRange = Upgrades[Level].Attack.AttackRangeMultipler;
	ResetHealth();
	BuildingName = "Wizards Tower";
}

void ABuilding_Wizards_Tower::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	FVector Location = GetActorLocation();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	BuildingDefender = GetWorld()->SpawnActor<AAllianceCharacter>(AAlliance_Wizard::StaticClass(), FVector(Location.X, Location.Y, 320), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
	if (BuildingDefender) {
		BuildingDefender->SpawnInit(this, Level, true, false);
		BuildingDefender->SetActorScale3D(FVector(0.7));
	}
}

void ABuilding_Wizards_Tower::Upgrade()
{
	Super::Upgrade();
}

void ABuilding_Wizards_Tower::Tick(float DeltaTime)
{

}

