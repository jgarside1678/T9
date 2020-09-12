// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Succubus.h"
#include "Components/CapsuleComponent.h"
#include "Enemy_Succubus_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "T9/Actors/Items/Tools/Item_Wooden_Pickaxe.h"

AEnemy_Succubus::AEnemy_Succubus(const FObjectInitializer& ObjectInitializer) {
	Levels.Add(1, FCharacterLevels{ 50, 0, 300, 0, 1000 });
	Levels.Add(2, FCharacterLevels{ 50, 0, 400, 0, 1000 });
	Levels.Add(3, FCharacterLevels{ 50, 0, 500, 0, 1000 });
	Levels.Add(4, FCharacterLevels{ 50, 0, 600, 0, 1000 });
	Levels.Add(5, FCharacterLevels{ 50, 0, 700, 0, 1000 });
	Levels.Add(6, FCharacterLevels{ 50, 0, 800, 0, 1000 });
	Levels.Add(7, FCharacterLevels{ 50, 0, 900, 0, 1000 });
	Levels.Add(8, FCharacterLevels{ 50, 0, 1000, 0, 1000 });
	Levels.Add(9, FCharacterLevels{ 50, 0, 1100, 0, 1000 });
	Levels.Add(10, FCharacterLevels{ 50, 0, 1200, 0, 1000 });
	Levels.Add(11, FCharacterLevels{ 50, 0, 1300, 0, 1000 });
	DeathTime = 1.8;
	AwarenessDistance = 2000;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AI/Enemies/ModularCharacterSuccubus/Meshes/OneMeshCharacter/SK_Succubus.SK_Succubus'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/AI/Enemies/ModularCharacterSuccubus/Animations/Succubus_Animation_BP.Succubus_Animation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/AI/Enemies/ModularCharacterSuccubus/Animations/Succubus_Anim_attack_Montage.Succubus_Anim_attack_Montage'"));
	//SetActorScale3D(FVector(2));
	if (MeshAsset.Succeeded()) {
		GetMesh()->SkeletalMesh = MeshAsset.Object;
		if (AnimationAsset.Succeeded()) {
			GetMesh()->AnimClass = AnimationAsset.Class;
		}
		if (AnimationMont.Succeeded()) {
			AttackMontage = AnimationMont.Object;
		}
	}
	AIControllerClass = AEnemy_Succubus_Controller::StaticClass();
	SetActorScale3D(FVector(2));
	DropTable.Add(FLoot{ 1, AItem_Wooden_Pickaxe::StaticClass() });
	DropTable.Add(FLoot{ 10, nullptr });
}


void AEnemy_Succubus::Attack(AActor* Target) {
	Super::Attack(Target);
}


void AEnemy_Succubus::SpecialAttack(AActor* Target) {
	CalculateDamage(50);
	Super::SpecialAttack(Target);
}

void AEnemy_Succubus::CalculateDamage(int BaseAdditionalDamage) {
	Super::CalculateDamage(BaseAdditionalDamage);
	if (CurrentPhase == Flying) Damage *= 2;
	else if (CurrentPhase == Channelling) Damage *= 3;
}

void AEnemy_Succubus::FlyingHeal()
{
	if (CurrentPhase == Flying && !IsDead) {
		SetCurrentHealth(CurrentHealth + 10);
		GetWorldTimerManager().SetTimer(FlyingHealHandle, this, &AEnemy_Succubus::FlyingHeal, 0.5, false);
	}
}


//void AEnemy_Succubus::Attack(AActor* Target, int Number) {
//	if (Target != CurrentTarget) {
//		AttackStreak = 0;
//		CurrentPhase = Normal;
//		CalculateDamage();
//	}
//	if (AttackStreak < 2) {
//		if (CurrentPhase != Channelling) {
//			CurrentMontage = AttackMontage;
//			PlayAnimMontage(CurrentMontage);
//		}
//		Super::Attack(Target);
//	}
//	else {
//		AttackStreak = 0;
//		SpecialAttack(Target, Number);
//	}
//}
//
//
//void AEnemy_Succubus::SpecialAttack(AActor* Target, int Number) {
//	if (Number == 0) Number = UKismetMathLibrary::RandomInteger64InRange(1, 2);
//	switch (Number) {
//	case 1:
//		if (CurrentPhase == Flying) CurrentPhase = Normal;
//		else {
//			CurrentPhase = Flying;
//			FlyingHeal();
//		}
//		break;
//	case 2:
//		if (CurrentPhase == Flying)	PlayAnimMontage(CurrentMontage);
//		else if (CurrentPhase == Channelling) CurrentPhase = Normal;
//		else CurrentPhase = Channelling;
//		break;
//	default:
//		break;
//
//	}
//	CalculateDamage();
//	DamageEnemy(Target, Damage);
//}