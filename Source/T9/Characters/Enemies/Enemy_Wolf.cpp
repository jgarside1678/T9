// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Wolf.h"
#include "T9/AI/Basic_Enemy_Controller.h"

AEnemy_Wolf::AEnemy_Wolf(const FObjectInitializer& ObjectInitializer) {
	HealthBarHeight = 200;
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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AI/Neutral/StylizedWildAnimals/Meshes/Wolf/SK_Wolf.SK_Wolf'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/AI/Neutral/StylizedWildAnimals/Animations/Wolf/WolfAnimation_BP.WolfAnimation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMont(TEXT("AnimMontage'/Game/AI/Neutral/StylizedWildAnimals/Animations/Wolf/Wolf_Attack_Montage.Wolf_Attack_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialMont(TEXT("AnimMontage'/Game/AI/Neutral/StylizedWildAnimals/Animations/Wolf/Wolf_SpecialAttack_Montage.Wolf_SpecialAttack_Montage'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh1Material(TEXT("MaterialInstanceConstant'/Game/AI/Neutral/StylizedWildAnimals/Materials/Instances/Wolf/MI_Wolf_Black.MI_Wolf_Black'"));
	if (Mesh1Material.Succeeded()) MeshMaterials.Add(Mesh1Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh2Material(TEXT("MaterialInstanceConstant'/Game/AI/Neutral/StylizedWildAnimals/Materials/Instances/Wolf/MI_Wolf_Blue.MI_Wolf_Blue'"));
	if (Mesh2Material.Succeeded()) MeshMaterials.Add(Mesh2Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh3Material(TEXT("MaterialInstanceConstant'/Game/AI/Neutral/StylizedWildAnimals/Materials/Instances/Wolf/MI_Wolf_Red.MI_Wolf_Red'"));
	if (Mesh3Material.Succeeded()) MeshMaterials.Add(Mesh3Material.Object);
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