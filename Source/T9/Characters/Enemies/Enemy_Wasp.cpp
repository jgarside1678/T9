// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Wasp.h"
#include "T9/AI/Basic_Enemy_Controller.h"

AEnemy_Wasp::AEnemy_Wasp(const FObjectInitializer& ObjectInitializer) {
	HealthBarHeight = 200;
	//FCharacterLevels:	Base Damage / AttackSpeed / AttackRange / MaxHealth / Armour / KillXP / KillGold
	Levels.Add(1, FCharacterLevels{ 50, 160, 0, 300, 50, 10, 25 });
	Levels.Add(2, FCharacterLevels{ 60, 160, 0, 400, 50, 10 , 25 });
	Levels.Add(3, FCharacterLevels{ 70, 160, 0, 500, 50, 20, 25 });
	Levels.Add(4, FCharacterLevels{ 80, 170, 0, 600, 50, 20, 25 });
	Levels.Add(5, FCharacterLevels{ 90, 170, 0, 700, 50, 30 , 25 });
	Levels.Add(6, FCharacterLevels{ 100, 170, 0, 800, 50, 30, 25 });
	Levels.Add(7, FCharacterLevels{ 120, 170, 0, 900, 50, 40, 25 });
	Levels.Add(8, FCharacterLevels{ 140, 170, 0, 1000, 50, 40, 25 });
	Levels.Add(9, FCharacterLevels{ 160, 200, 0, 1100, 50, 50 , 25 });
	Levels.Add(10, FCharacterLevels{ 180, 200, 0, 1200, 50, 50, 25 });
	Levels.Add(11, FCharacterLevels{ 200, 200, 0, 1300, 50, 60 , 25 });
	DeathTime = 4;
	AwarenessDistance = 1200;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedFantasyForestCreatures/Meshes/SK_Wasp.SK_Wasp'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Enemies/StylizedFantasyForestCreatures/Animations/Wasp_Animation_BP.Wasp_Animation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMont(TEXT("AnimMontage'/Game/Units/Enemies/StylizedFantasyForestCreatures/Animations/Wasp_Attack_Montage.Wasp_Attack_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialMont(TEXT("AnimMontage'/Game/Units/Enemies/StylizedFantasyForestCreatures/Animations/Wasp_Special_Montage.Wasp_Special_Montage'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh1Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Wasp_Blue.MI_Wasp_Blue'"));
	if (Mesh1Material.Succeeded()) MeshMaterials.Add(Mesh1Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh2Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Wasp_Green.MI_Wasp_Green'"));
	if (Mesh2Material.Succeeded()) MeshMaterials.Add(Mesh2Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh3Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Wasp_Purple.MI_Wasp_Purple'"));
	if (Mesh3Material.Succeeded()) MeshMaterials.Add(Mesh3Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh4Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Wasp_Yellow.MI_Wasp_Yellow'"));
	if (Mesh4Material.Succeeded()) MeshMaterials.Add(Mesh4Material.Object);
	if (MeshAsset.Succeeded()) {
		GetMesh()->SkeletalMesh = MeshAsset.Object;
		if (AnimationAsset.Succeeded()) {
			GetMesh()->AnimClass = AnimationAsset.Class;
		}
		if (AttackMont.Succeeded()) {
			AttackMontage = AttackMont.Object;
		}
		if (SpecialMont.Succeeded()) {
			SpecialAttackMontage = SpecialMont.Object;
		}
	}
	if (MeshMaterials.Num() > 0) GetMesh()->SetMaterial(0, MeshMaterials[FMath::RandRange(0, MeshMaterials.Num() - 1)]);
	AIControllerClass = ABasic_Enemy_Controller::StaticClass();
}

