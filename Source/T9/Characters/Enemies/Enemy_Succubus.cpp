// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Succubus.h"
#include "Components/CapsuleComponent.h"
#include "T9/AI/Basic_Enemy_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "T9/Actors/Items/Tools/Item_Wooden_Pickaxe.h"

AEnemy_Succubus::AEnemy_Succubus(const FObjectInitializer& ObjectInitializer) {
	//FCharacterLevels:	Base Damage / AttackSpeed / AttackRange / MaxHealth / Armour / KillXP / KillGold
	Levels.Add(1, FCharacterLevels{ 50, 150, 0, 300, 0, 50, 50 });
	Levels.Add(2, FCharacterLevels{ 50, 150, 0, 400, 0, 50, 50 });
	Levels.Add(3, FCharacterLevels{ 50, 150, 0, 500, 0, 50, 50 });
	Levels.Add(4, FCharacterLevels{ 50, 150, 0, 600, 0, 50, 50 });
	Levels.Add(5, FCharacterLevels{ 50, 150, 0, 700, 0, 50, 50 });
	Levels.Add(6, FCharacterLevels{ 50, 150, 0, 800, 0, 50, 50 });
	Levels.Add(7, FCharacterLevels{ 50, 150, 0, 900, 0, 50, 50 });
	Levels.Add(8, FCharacterLevels{ 50, 150, 0, 1000, 0, 50, 50 });
	Levels.Add(9, FCharacterLevels{ 50, 150, 0, 1100, 0, 50, 50 });
	Levels.Add(10, FCharacterLevels{ 50, 150, 0, 1200, 0, 50, 50 });
	Levels.Add(11, FCharacterLevels{ 50, 150, 0, 1300, 0, 50, 50 });
	DeathTime = 1.8;
	AwarenessDistance = 2000;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Units/Enemies/ModularCharacterSuccubus/Meshes/OneMeshCharacter/SK_Succubus.SK_Succubus'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Enemies/ModularCharacterSuccubus/Animations/Succubus_Animation_BP.Succubus_Animation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/Units/Enemies/ModularCharacterSuccubus/Animations/Succubus_Anim_attack_Montage.Succubus_Anim_attack_Montage'"));
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
	AIControllerClass = ABasic_Enemy_Controller::StaticClass();
	SetActorScale3D(FVector(2));
	DropTable.Add(FLoot{ 1, AItem_Wooden_Pickaxe::StaticClass() });
	DropTable.Add(FLoot{ 10, nullptr });
}



void AEnemy_Succubus::SpecialAttack() {
	CalculateDamage(50);
	Super::SpecialAttack();
}

void AEnemy_Succubus::CalculateDamage(int BaseAdditionalDamage, float AdditionalDamageMultiplier) {
	if (CurrentPhase == Flying) Super::CalculateDamage(BaseAdditionalDamage, AdditionalDamageMultiplier*2);
	else if (CurrentPhase == Channelling) Super::CalculateDamage(BaseAdditionalDamage, AdditionalDamageMultiplier * 3);
	else Super::CalculateDamage(BaseAdditionalDamage, AdditionalDamageMultiplier);
}

void AEnemy_Succubus::FlyingHeal()
{
	if (CurrentPhase == Flying && !IsDead) {
		SetCurrentHealth(CurrentHealth + 10);
		GetWorldTimerManager().SetTimer(FlyingHealHandle, this, &AEnemy_Succubus::FlyingHeal, 0.5, false);
	}
}
