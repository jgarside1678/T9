// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_Ballista_Tower.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "T9/Actors/Projectiles/Projectile_Ballista_Arrow.h"

ABuilding_Ballista_Tower::ABuilding_Ballista_Tower(const FObjectInitializer& ObjectInitializer) {
	// XP / Cost / Maxhealth / Damage
	Type = Turret;
	GridLength = FVector2D(3);
	TurretStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretStaticMeshComponent->SetupAttachment(StaticMeshComponent);
	TurretStaticMeshComponent->SetRelativeLocation(FVector(0, 0, 330.0));
	TurretStaticMeshComponent->SetCanEverAffectNavigation(false);
	Projectile = AProjectile_Ballista_Arrow::StaticClass();
	ProjectileSpawn->SetupAttachment(TurretStaticMeshComponent);
	ProjectileSpawn->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	ProjectileDelay = 0.5f;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base3A.Tower_Base3A'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh1(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base3B.Tower_Base3B'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh2(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base3C.Tower_Base3C'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Turret_Crossbow1_Turret.Turret_Crossbow1_Turret'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh1(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Turret_Crossbow2_Turret.Turret_Crossbow2_Turret'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh2(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Turret_Crossbow3_Turret.Turret_Crossbow3_Turret'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageLevel1(TEXT("Texture2D'/Game/UI/Assets/Sprites/WatchTowerImage.WatchTowerImage'"));
	if (BaseMesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(BaseMesh.Object);
	}
	if (TurretMesh.Succeeded())		TurretStaticMeshComponent->SetStaticMesh(TurretMesh.Object);
	//{Level, FBuildingUpgrades{XP, PowerRating, Maxhealth, Defence, FBuildingCosts{Gold, Wood, Stone, Food}, FBuildingAttack{Damage, AttackSpeed, AttackRange}, FBuildingProduction{Gold, Wood, Stone, Food}}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 100, 1000.0f, 10.0f, ImageLevel1.Object, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{40, 100, 10}, FBuildingProduction{} });
	Upgrades.Add(2, FBuildingUpgrades{ 250.0f, 200, 5000.0f, 50.0f, ImageLevel1.Object,FBuildingCosts{250, 20, 20, 20}, FBuildingAttack{60, 100, 10}, FBuildingProduction{}, BaseMesh1.Object, TurretMesh1.Object });
	Upgrades.Add(3, FBuildingUpgrades{ 500.0f, 300, 10000.0f, 100.0f, ImageLevel1.Object, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{100, 100, 10}, FBuildingProduction{}, BaseMesh2.Object, TurretMesh2.Object });
	BuildingDetectionRange = Upgrades[Level].Attack.AttackRangeMultipler;
	ResetHealth();
	BuildingName = "Ballista Tower";
}

void ABuilding_Ballista_Tower::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding_Ballista_Tower::Upgrade()
{
	Super::Upgrade();
	if (Upgrades[Level].TurretMesh && TurretStaticMeshComponent) TurretStaticMeshComponent->SetStaticMesh(Upgrades[Level].TurretMesh);
}

void ABuilding_Ballista_Tower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
