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
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh1Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Green.MI_Spider_Green'"));
	//if (Mesh1Material.Succeeded()) MeshMaterials.Add(Mesh1Material.Object);
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh2Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Orange.MI_Spider_Orange'"));
	//if (Mesh2Material.Succeeded()) MeshMaterials.Add(Mesh2Material.Object);
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh3Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Purple.MI_Spider_Purple'"));
	//if (Mesh3Material.Succeeded()) MeshMaterials.Add(Mesh3Material.Object);
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh4Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Brown.MI_Spider_Brown'"));
	//if (Mesh4Material.Succeeded()) MeshMaterials.Add(Mesh4Material.Object);
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
	if (MeshMaterials.Num() > 0) GetMesh()->SetMaterial(0, MeshMaterials[FMath::RandRange(0, MeshMaterials.Num() - 1)]);
	AIControllerClass = ABasic_Enemy_Controller::StaticClass();
	ChangeMovementSpeed(150);
}
