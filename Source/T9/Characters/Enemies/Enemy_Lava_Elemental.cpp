// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Lava_Elemental.h"
#include "Components/CapsuleComponent.h"
#include "T9/AI/Enemy_Lich_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "T9/Actors/Projectiles/Projectile_Magic_DeathsDecay.h"
#include "T9/Actors/Items/Tools/Item_Wooden_Pickaxe.h"


AEnemy_Lava_Elemental::AEnemy_Lava_Elemental(const FObjectInitializer& ObjectInitializer) {
	HealthBarHeight = 400;
	Projectile = AProjectile_Magic_DeathsDecay::StaticClass();
	Levels.Add(1, FCharacterLevels{ 100, 500, 3000, 50, 10000 });
	Levels.Add(2, FCharacterLevels{ 300, 500, 4000, 50, 10000 });
	Levels.Add(3, FCharacterLevels{ 300, 500, 5000, 50, 10000 });
	Levels.Add(4, FCharacterLevels{ 300, 500, 6000, 50, 10000 });
	Levels.Add(5, FCharacterLevels{ 300, 500, 7000, 50, 10000 });
	Levels.Add(6, FCharacterLevels{ 300, 500, 8000, 50, 10000 });
	Levels.Add(7, FCharacterLevels{ 300, 500, 9000, 50, 10000 });
	Levels.Add(8, FCharacterLevels{ 300, 500, 10000, 50, 10000 });
	Levels.Add(9, FCharacterLevels{ 300, 500, 11000, 50, 10000 });
	Levels.Add(10, FCharacterLevels{ 300, 500, 12000, 50, 10000 });
	Levels.Add(11, FCharacterLevels{ 300, 500, 13000, 50, 10000 });
	DeathTime = 4;
	AwarenessDistance = 2000;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AI/Enemies/StylizedLavaElemental/Meshes/SK_LavaElemental.SK_LavaElemental'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/AI/Enemies/StylizedLavaElemental/Animations/LavaElementalAnimation_BP.LavaElementalAnimation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMont(TEXT("AnimMontage'/Game/AI/Enemies/StylizedLavaElemental/Animations/LavaElemental_Attack_Montage.LavaElemental_Attack_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialMont(TEXT("AnimMontage'/Game/AI/Enemies/StylizedLavaElemental/Animations/LavaElemental_Special_Montage.LavaElemental_Special_Montage'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Phase1Material(TEXT("MaterialInstanceConstant'/Game/AI/Enemies/StylizedLavaElemental/Materials/Instances/MI_LavaElemental_Red.MI_LavaElemental_Red'"));
	if (Phase1Material.Succeeded()) PhaseMaterials.Add(Phase1Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Phase2Material(TEXT("MaterialInstanceConstant'/Game/AI/Enemies/StylizedLavaElemental/Materials/Instances/MI_LavaElemental_Cyan.MI_LavaElemental_Cyan'"));
	if (Phase2Material.Succeeded()) PhaseMaterials.Add(Phase2Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Phase3Material(TEXT("MaterialInstanceConstant'/Game/AI/Enemies/StylizedLavaElemental/Materials/Instances/MI_LavaElemental_Gold.MI_LavaElemental_Gold'"));
	if (Phase3Material.Succeeded()) PhaseMaterials.Add(Phase3Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Phase4Material(TEXT("MaterialInstanceConstant'/Game/AI/Enemies/StylizedLavaElemental/Materials/Instances/MI_LavaElemental_Green.MI_LavaElemental_Green'"));
	if (Phase4Material.Succeeded()) PhaseMaterials.Add(Phase4Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Phase5Material(TEXT("MaterialInstanceConstant'/Game/AI/Enemies/StylizedLavaElemental/Materials/Instances/MI_LavaElemental_Purple.MI_LavaElemental_Purple'"));
	if (Phase5Material.Succeeded()) PhaseMaterials.Add(Phase5Material.Object);
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
	AIControllerClass = AEnemy_Lich_Controller::StaticClass();
	SetActorScale3D(FVector(3));
	//DropTable.Add(FLoot{ 1, AItem_Wooden_Pickaxe::StaticClass() });
	DropTable.Add(FLoot{ 10, nullptr });
}

TEnumAsByte<LavaElementalPhase> AEnemy_Lava_Elemental::GetCurrentPhase()
{
	return CurrentPhase;
}

void AEnemy_Lava_Elemental::Attack(AActor* Target)
{
	Super::Attack(Target);
}

void AEnemy_Lava_Elemental::SpecialAttack(AActor* Target)
{
	Heal(0.3);
	Super::SpecialAttack(Target);
}

void AEnemy_Lava_Elemental::TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage)
{
	Super::TakeDamage(AttackingActor, AmountOfDamage, TypeDamage);
	if (CurrentHealth < MaxHealth * 0.2)ChangePhase(4);
	else if (CurrentHealth < MaxHealth * 0.4 && (int)CurrentPhase < 4)ChangePhase(3);
	else if (CurrentHealth < MaxHealth * 0.6 && (int)CurrentPhase < 3)ChangePhase(2);
	else if (CurrentHealth < MaxHealth * 0.8 && (int)CurrentPhase < 2)ChangePhase(1);
}

void AEnemy_Lava_Elemental::ChangePhase(int NewPhase)
{
	switch (NewPhase) {
	case 0:
		CurrentPhase = Red;
		CalculateDamage(50);
		break;
	case 1:
		CurrentPhase = Cyan;
		CalculateDamage(100);
		break;
	case 2:
		CurrentPhase = Gold;
		break;
	case 3:
		CurrentPhase = Green;
		break;
	case 4:
		CurrentPhase = Purple;
		break;
	default:
		break;
	}
	GetMesh()->SetMaterial(0, PhaseMaterials[CurrentPhase]);
}

void AEnemy_Lava_Elemental::CalculateDamage(int BaseAdditionalDamage)
{
	Super::CalculateDamage(BaseAdditionalDamage);
}

