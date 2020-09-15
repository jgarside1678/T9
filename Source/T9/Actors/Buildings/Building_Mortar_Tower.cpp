// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_Mortar_Tower.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "T9/Actors/Projectiles/Projectile_Mortar.h"

ABuilding_Mortar_Tower::ABuilding_Mortar_Tower(const FObjectInitializer& ObjectInitializer) {
	// XP / Cost / Maxhealth / Damage
	Type = Turret;
	GridLength = FVector2D(3);
	TurretStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretStaticMeshComponent->SetupAttachment(StaticMeshComponent);
	TurretStaticMeshComponent->SetRelativeLocation(FVector(0, 0, 265.0));
	TurretStaticMeshComponent->SetCanEverAffectNavigation(false);
	Projectile = AProjectile_Mortar::StaticClass();
	ProjectileSpawn->SetupAttachment(TurretStaticMeshComponent);
	ProjectileSpawn->SetRelativeLocation(FVector(0.0f, 10.0f, 20.0f));
	ProjectileDelay = 0.5f;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh1(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1A.Tower_Base1A'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh2(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1B.Tower_Base1B'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh3(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1C.Tower_Base1C'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh1(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Turret_Mortar1.Turret_Mortar1'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh2(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Turret_Mortar2.Turret_Mortar2'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh3(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Turret_Mortar3.Turret_Mortar3'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretMesh4(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Turret_Mortar4.Turret_Mortar4'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageLevel1(TEXT("Texture2D'/Game/UI/Assets/Sprites/WatchTowerImage.WatchTowerImage'"));
	if (BaseMesh1.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(BaseMesh1.Object);
	}
	if (TurretMesh1.Succeeded())		TurretStaticMeshComponent->SetStaticMesh(TurretMesh1.Object);
	//{Level, FBuildingUpgrades{XP, PowerRating, Maxhealth, Defence, FBuildingCosts{Gold, Wood, Stone, Food}, FBuildingAttack{Damage, AttackSpeed, AttackRange}, FBuildingProduction{Gold, Wood, Stone, Food}}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 100, 1000.0f, 10.0f, ImageLevel1.Object, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{40, 100, 20}, FBuildingProduction{} });
	Upgrades.Add(2, FBuildingUpgrades{ 250.0f, 200, 5000.0f, 50.0f, ImageLevel1.Object,FBuildingCosts{250, 20, 20, 20}, FBuildingAttack{60, 100, 20}, FBuildingProduction{}, BaseMesh1.Object, TurretMesh2.Object });
	Upgrades.Add(3, FBuildingUpgrades{ 500.0f, 300, 10000.0f, 100.0f, ImageLevel1.Object, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{100, 100, 20}, FBuildingProduction{}, BaseMesh2.Object, TurretMesh2.Object });
	Upgrades.Add(4, FBuildingUpgrades{ 500.0f, 300, 10000.0f, 100.0f, ImageLevel1.Object, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{100, 100, 20}, FBuildingProduction{}, BaseMesh2.Object, TurretMesh3.Object });
	Upgrades.Add(5, FBuildingUpgrades{ 500.0f, 300, 10000.0f, 100.0f, ImageLevel1.Object, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{100, 100, 20}, FBuildingProduction{}, BaseMesh3.Object, TurretMesh3.Object });
	Upgrades.Add(6, FBuildingUpgrades{ 500.0f, 300, 10000.0f, 100.0f, ImageLevel1.Object, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{100, 100, 20}, FBuildingProduction{}, BaseMesh3.Object, TurretMesh4.Object });
	//BuildingDetectionRange = Upgrades[Level].Attack.AttackRangeMultipler;
	ResetHealth();
	BuildingName = "Mortar Tower";
}

void ABuilding_Mortar_Tower::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding_Mortar_Tower::Upgrade()
{
	Super::Upgrade();
	if (Upgrades[Level].TurretMesh && TurretStaticMeshComponent) TurretStaticMeshComponent->SetStaticMesh(Upgrades[Level].TurretMesh);
}

void ABuilding_Mortar_Tower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
