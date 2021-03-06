// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Arrow_Tower.h"
#include "T9/MainPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "T9/MainPlayerState.h"
#include "T9/Characters/Alliance/Alliance_Wizard.h"
#include "T9/Actors/Projectiles/Projectile_Arrow.h"


ABuilding_Arrow_Tower::ABuilding_Arrow_Tower(const FObjectInitializer& ObjectInitializer) {
	// XP / Cost / Maxhealth / Damage
	Type = Character;
	Projectile = AProjectile_Arrow::StaticClass();
	GridLength = FVector2D(3);
	//ProjectileSpawn->SetRelativeLocation(FVector(0,0,0.0f));
	ProjectileDelay = 0.9f;
	DefenderDisplacement = CreateDefaultSubobject<USceneComponent>(TEXT("Defender Displacement"));
	DefenderDisplacement->SetupAttachment(StaticMeshComponent);
	DefenderDisplacement->SetRelativeLocation(FVector(0, 0, 255));
	DefenderDisplacement->SetRelativeRotation(FRotator(0, 0, 0));
	BuildingDefender = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Building Defender"));
	BuildingDefender->SetupAttachment(DefenderDisplacement);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh1(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Towers/Tower_Base1A.Tower_Base1A'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh2(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Towers/Tower_Base1B.Tower_Base1B'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh3(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Towers/Tower_Base1C.Tower_Base1C'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageLevel1(TEXT("Texture2D'/Game/UI/Assets/Sprites/WatchTowerImage.WatchTowerImage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/Units/Alliance/StylizedHumanFemale/Animations/Alliance_Wizard_TowerFemale_Attack.Alliance_Wizard_TowerFemale_Attack'"));
	if (AnimationMont.Succeeded()) DefenderAttackAnimation = AnimationMont.Object;
	if (BaseMesh1.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(BaseMesh1.Object);
	}
	//{Level, FBuildingUpgrades{XP, PowerRating, Maxhealth, Defence, FBuildingCosts{Gold, Wood, Stone, Food}, FBuildingAttack{Damage, AttackSpeed, AttackRange}, FBuildingProduction{Gold, Wood, Stone, Food}}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 50, 1000.0f, 10.0f, ImageLevel1.Object,FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{40, 100, 10}, FBuildingProduction{} });
	Upgrades.Add(2, FBuildingUpgrades{ 250.0f, 100, 5000.0f, 10.0f, ImageLevel1.Object,FBuildingCosts{250, 20, 20, 20}, FBuildingAttack{60, 100, 10}, FBuildingProduction{}, BaseMesh2.Object });
	Upgrades.Add(3, FBuildingUpgrades{ 500.0f, 150, 10000.0f, 10.0f, ImageLevel1.Object, FBuildingCosts{500, 50, 50, 50}, FBuildingAttack{200, 100, 10}, FBuildingProduction{}, BaseMesh3.Object });
	BuildingDetectionRange = Upgrades[Level].Attack.AttackRangeMultipler;
	ResetHealth();
	BuildingName = "Arrow Tower";

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanFemale/Meshes/SK_Body.SK_Body'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeltMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanFemale/Meshes/ModularParts/Peasant/SK_Peasant_Belt.SK_Peasant_Belt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BootsMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanFemale/Meshes/ModularParts/Peasant/SK_Peasant_Boots.SK_Peasant_Boots'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> BrowsMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Brows_02.SK_Brows_02'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HairMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanFemale/Meshes/ModularParts/Hairstyles/SK_Hair_06.SK_Hair_06'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LowerBodyMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanFemale/Meshes/ModularParts/Peasant/SK_Peasant_Pants.SK_Peasant_Pants'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> UpperBodyMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanFemale/Meshes/ModularParts/Peasant/SK_Peasant_Shirt_NoSleeves.SK_Peasant_Shirt_NoSleeves'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeardMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Beard_02.SK_Beard_02'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMesh(TEXT("StaticMesh'/Game/Meshes/Weapons/Pickaxe.Pickaxe'"));
	if (BodyMesh.Succeeded())MeshPeices.Add(BodyMesh.Object);
	if (BeltMesh.Succeeded())MeshPeices.Add(BeltMesh.Object);
	if (BootsMesh.Succeeded())MeshPeices.Add(BootsMesh.Object);
	//if (BrowsMesh.Succeeded())MeshPeices.Add(BrowsMesh.Object);
	if (HairMesh.Succeeded())MeshPeices.Add(HairMesh.Object);
	if (LowerBodyMesh.Succeeded())MeshPeices.Add(LowerBodyMesh.Object);
	if (UpperBodyMesh.Succeeded())MeshPeices.Add(UpperBodyMesh.Object);
	//if (BeardMesh.Succeeded())MeshPeices.Add(BeardMesh.Object);
	//MeshInit();
	if (MeshPeices.Num() > 0 && MeshPeices[0]->Skeleton) BuildingDefender->SetSkeletalMesh(MergeMeshes(FSkeletalMeshMergeParams(MeshPeices, MeshPeices[0]->Skeleton)));
	//if (ItemMesh.Succeeded()) {
	//	MainHandItemMesh->SetStaticMesh(ItemMesh.Object);
	//	MainHandItemMesh->SetRelativeScale3D(FVector(0.5));
	//	MainHandItemMesh->SetRelativeLocation(FVector(22.000000, -59.000000, 31.000000));
	//	MainHandItemMesh->SetRelativeRotation(FRotator(0, 309.599152f, 0));
	//}


	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Alliance/StylizedHumanFemale/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
	if (AnimationAsset.Succeeded()) {
		BuildingDefender->AnimClass = AnimationAsset.Class;
	}
}

void ABuilding_Arrow_Tower::BeginPlay()
{
	Super::BeginPlay();

}

void ABuilding_Arrow_Tower::Upgrade()
{
	Super::Upgrade();
}

void ABuilding_Arrow_Tower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
