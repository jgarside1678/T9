// Copyright T9 2020


#include "Enemy_Skeleton_Archer.h"
#include "T9/Actors/Projectiles/Projectile_Arrow.h"
#include "T9/AI/Basic_Enemy_Controller.h"

AEnemy_Skeleton_Archer::AEnemy_Skeleton_Archer(const FObjectInitializer& ObjectInitializer) {
	HealthBarHeight = 200;
	Projectile = AProjectile_Arrow::StaticClass();
	RelativeProjectileSpawnLocation = FVector(100, 0, 0);
	//FCharacterLevels:	Base Damage / AttackSpeed / AttackRange / MaxHealth / Armour / KillXP / KillGold
	Levels.Add(1, FCharacterLevels{ 50, 160, 600, 300, 50, 10, 25 });
	Levels.Add(2, FCharacterLevels{ 60, 160, 600, 400, 50, 10 , 25 });
	Levels.Add(3, FCharacterLevels{ 70, 160, 600, 500, 50, 20, 25 });
	Levels.Add(4, FCharacterLevels{ 80, 170, 600, 600, 50, 20, 25 });
	Levels.Add(5, FCharacterLevels{ 90, 170, 600, 700, 50, 30 , 25 });
	Levels.Add(6, FCharacterLevels{ 100, 170, 600, 800, 50, 30, 25 });
	Levels.Add(7, FCharacterLevels{ 120, 170, 600, 900, 50, 40, 25 });
	Levels.Add(8, FCharacterLevels{ 140, 170, 600, 1000, 50, 40, 25 });
	Levels.Add(9, FCharacterLevels{ 160, 200, 600, 1100, 50, 50 , 25 });
	Levels.Add(10, FCharacterLevels{ 180, 200, 600, 1200, 50, 50, 25 });
	Levels.Add(11, FCharacterLevels{ 200, 200, 600, 1300, 50, 60 , 25 });
	DeathTime = 4;
	AwarenessDistance = 1200;
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Enemies/StylizedEnemyNPC/Animations/SkeletonArcher/Skeleton_Archer_Animation_BP.Skeleton_Archer_Animation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMont(TEXT("AnimMontage'/Game/Units/Enemies/StylizedEnemyNPC/Animations/SkeletonArcher/Skeleton_Archer_Attack_Montage.Skeleton_Archer_Attack_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialMont(TEXT("AnimMontage'/Game/Units/Enemies/StylizedEnemyNPC/Animations/SkeletonArcher/Skeleton_Archer_Special_Attack_Montage.Skeleton_Archer_Special_Attack_Montage'"));

	//Materials
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh1MaterialArmour(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Armor_Black.MI_SkeletonArcher_Armor_Black'"));
	if (Mesh1MaterialArmour.Succeeded()) MeshMaterialsArmour.Add(Mesh1MaterialArmour.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh2MaterialArmour(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Armor_Green.MI_SkeletonArcher_Armor_Green'"));
	if (Mesh2MaterialArmour.Succeeded()) MeshMaterialsArmour.Add(Mesh2MaterialArmour.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh3MaterialArmour(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Armor_Yellow.MI_SkeletonArcher_Armor_Yellow'"));
	if (Mesh3MaterialArmour.Succeeded()) MeshMaterialsArmour.Add(Mesh3MaterialArmour.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh1MaterialBody(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Body_Black.MI_SkeletonArcher_Body_Black'"));
	if (Mesh1MaterialBody.Succeeded()) MeshMaterialsBody.Add(Mesh1MaterialBody.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh2MaterialBody(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Body_Green.MI_SkeletonArcher_Body_Green'"));
	if (Mesh2MaterialBody.Succeeded()) MeshMaterialsBody.Add(Mesh2MaterialBody.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh3MaterialBody(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Body_Yellow.MI_SkeletonArcher_Body_Yellow'"));
	if (Mesh3MaterialBody.Succeeded()) MeshMaterialsBody.Add(Mesh3MaterialBody.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh1MaterialBow(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Bow_Black.MI_SkeletonArcher_Bow_Black'"));
	if (Mesh1MaterialBow.Succeeded()) MeshMaterialsBow.Add(Mesh1MaterialBow.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh2MaterialBow(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Bow_Green.MI_SkeletonArcher_Bow_Green'"));
	if (Mesh2MaterialBow.Succeeded()) MeshMaterialsBow.Add(Mesh2MaterialBow.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh3MaterialBow(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedEnemyNPC/Materials/Instances/SkeletonArcher/MI_SkeletonArcher_Bow_Yellow.MI_SkeletonArcher_Bow_Yellow'"));
	if (Mesh3MaterialBow.Succeeded()) MeshMaterialsBow.Add(Mesh3MaterialBow.Object);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/Weapons/SK_Bow_v2.SK_Bow_v2'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/SK_Skeleton.SK_Skeleton'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HelmetMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_Helm.SK_Helm'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BootsMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_Boots.SK_Boots'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ChestPieceMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_Chestpiece.SK_Chestpiece'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyBeltMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_BodyBelt.SK_BodyBelt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KneePadsMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_Kneepads.SK_Kneepads'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ShoulderPadsMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_Shoulder.SK_Shoulder'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkirtMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_Skirt.SK_Skirt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Quiver(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonArcher/ModularBodyParts/SK_Quiver.SK_Quiver'"));
	if (WeaponMesh.Succeeded())MeshPeices.Add(WeaponMesh.Object);
	if (BodyMesh.Succeeded())MeshPeices.Add(BodyMesh.Object);
	if (HelmetMesh.Succeeded())MeshPeices.Add(HelmetMesh.Object);
	if (BootsMesh.Succeeded())MeshPeices.Add(BootsMesh.Object);
	if (ChestPieceMesh.Succeeded())MeshPeices.Add(ChestPieceMesh.Object);
	if (BodyBeltMesh.Succeeded())MeshPeices.Add(BodyBeltMesh.Object);
	if (KneePadsMesh.Succeeded())MeshPeices.Add(KneePadsMesh.Object);
	if (ShoulderPadsMesh.Succeeded())MeshPeices.Add(ShoulderPadsMesh.Object);
	if (SkirtMesh.Succeeded())MeshPeices.Add(SkirtMesh.Object);
	if (Quiver.Succeeded())MeshPeices.Add(Quiver.Object);
	GetMesh()->SetSkeletalMesh(MergeMeshes(FSkeletalMeshMergeParams(MeshPeices, MeshPeices[0]->Skeleton)));
	if (AnimationAsset.Succeeded()) {
		GetMesh()->AnimClass = AnimationAsset.Class;
	}
	if (AttackMont.Succeeded()) {
		AttackMontage = AttackMont.Object;
	}
	if (SpecialMont.Succeeded()) {
		SpecialAttackMontage = SpecialMont.Object;
	}
	int MaterialIndex = FMath::RandRange(0, MeshMaterialsBow.Num() - 1);
	if (MeshMaterialsBow.Num() > 0 && MaterialIndex <= MeshMaterialsBow.Num()-1) GetMesh()->SetMaterial(0, MeshMaterialsBow[MaterialIndex]);
	if (MeshMaterialsBody.Num() > 0 && MaterialIndex <= MeshMaterialsBody.Num() - 1) GetMesh()->SetMaterial(1, MeshMaterialsBody[MaterialIndex]);
	if (MeshMaterialsArmour.Num() > 0 && MaterialIndex <= MeshMaterialsArmour.Num() - 1) GetMesh()->SetMaterial(2, MeshMaterialsArmour[MaterialIndex]);
	AIControllerClass = ABasic_Enemy_Controller::StaticClass();
	ChangeMovementSpeed(150);
}
