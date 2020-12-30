// Copyright T9 2020


#include "Enemy_Skeleton_Warrior.h"
#include "T9/AI/Basic_Enemy_Controller.h"

AEnemy_Skeleton_Warrior::AEnemy_Skeleton_Warrior(const FObjectInitializer& ObjectInitializer) {
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
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Enemies/StylizedEnemyNPC/Animations/SkeletonWarrior/Skeleton_Warrior_Animation_BP.Skeleton_Warrior_Animation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMont(TEXT("AnimMontage'/Game/Units/Enemies/StylizedEnemyNPC/Animations/SkeletonWarrior/Skeleton_Warrior_Attack_Montage.Skeleton_Warrior_Attack_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialMont(TEXT("AnimMontage'/Game/Units/Enemies/StylizedFantasyForestCreatures/Animations/Spider_Special_Montage.Spider_Special_Montage'"));

	//Materials
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh1Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Green.MI_Spider_Green'"));
	//if (Mesh1Material.Succeeded()) MeshMaterials.Add(Mesh1Material.Object);
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh2Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Orange.MI_Spider_Orange'"));
	//if (Mesh2Material.Succeeded()) MeshMaterials.Add(Mesh2Material.Object);
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh3Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Purple.MI_Spider_Purple'"));
	//if (Mesh3Material.Succeeded()) MeshMaterials.Add(Mesh3Material.Object);
	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> Mesh4Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/StylizedFantasyForestCreatures/Materials/Instances/MI_Spider_Brown.MI_Spider_Brown'"));
	//if (Mesh4Material.Succeeded()) MeshMaterials.Add(Mesh4Material.Object);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/SK_Skeleton.SK_Skeleton'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HelmetMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/ModularBodyParts/SK_Helmet.SK_Helmet'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BootsMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/ModularBodyParts/SK_Boots.SK_Boots'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ChestClothMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/ModularBodyParts/SK_ChestCloth.SK_ChestCloth'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ChestBeltMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/ModularBodyParts/SK_ChestBelt.SK_ChestBelt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KneePadsMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/ModularBodyParts/SK_KneePads.SK_KneePads'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ShoulderPadLMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/ModularBodyParts/SK_ShoulderPad_L_02.SK_ShoulderPad_L_02'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ShoulderPadRMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/ModularBodyParts/SK_ShoulderPad_R_02.SK_ShoulderPad_R_02'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Weapon(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/Weapons/SkeletonWarriorSword.SkeletonWarriorSword'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ShieldMesh(TEXT("SkeletalMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/Weapons/SkeletonShield.SkeletonShield'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMainHandItem(TEXT("StaticMesh'/Game/Units/Enemies/StylizedEnemyNPC/Meshes/SkeletonWarrior/Weapons/SM_Sword_1h.SM_Sword_1h'"));
	if (BodyMesh.Succeeded())MeshPeices.Add(BodyMesh.Object);
	if (Weapon.Succeeded())MeshPeices.Add(Weapon.Object);
	if (ShieldMesh.Succeeded())MeshPeices.Add(ShieldMesh.Object);
	if (HelmetMesh.Succeeded())MeshPeices.Add(HelmetMesh.Object);
	if (BootsMesh.Succeeded())MeshPeices.Add(BootsMesh.Object);
	if (ChestClothMesh.Succeeded())MeshPeices.Add(ChestClothMesh.Object);
	if (ChestBeltMesh.Succeeded())MeshPeices.Add(ChestBeltMesh.Object);
	if (KneePadsMesh.Succeeded())MeshPeices.Add(KneePadsMesh.Object);
	if (ShoulderPadLMesh.Succeeded())MeshPeices.Add(ShoulderPadLMesh.Object);
	if (ShoulderPadRMesh.Succeeded())MeshPeices.Add(ShoulderPadRMesh.Object);
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
	ChangeMovementSpeed(250);
}
