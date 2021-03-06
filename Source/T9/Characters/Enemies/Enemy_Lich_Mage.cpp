// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Lich_Mage.h"
#include "Components/CapsuleComponent.h"
#include "T9/AI/Basic_Enemy_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "T9/Actors/Projectiles/Projectile_Magic_DeathsDecay.h"
#include "T9/Actors/Items/Tools/Item_Wooden_Pickaxe.h"
#include "T9/Characters/Enemies/Enemy_Skeleton_Warrior.h"
#include "T9/Characters/Enemies/Enemy_Skeleton_Archer.h"


AEnemy_Lich_Mage::AEnemy_Lich_Mage(const FObjectInitializer& ObjectInitializer) {
	Projectile = AProjectile_Magic_DeathsDecay::StaticClass();
	Levels.Add(1, FCharacterLevels{ 100, 150, 500, 1500, 0, 100, 50 });
	Levels.Add(2, FCharacterLevels{ 300, 150, 500, 400, 0, 100, 50 });
	Levels.Add(3, FCharacterLevels{ 300, 150, 500, 500, 0, 100, 50 });
	Levels.Add(4, FCharacterLevels{ 300, 150, 500, 600, 0, 100, 50 });
	Levels.Add(5, FCharacterLevels{ 300, 150, 500, 700, 0, 100, 50 });
	Levels.Add(6, FCharacterLevels{ 300, 150, 500, 800, 0, 100, 50 });
	Levels.Add(7, FCharacterLevels{ 300, 150, 500, 900, 0, 100, 50 });
	Levels.Add(8, FCharacterLevels{ 300, 150, 500, 1000, 0, 100, 50 });
	Levels.Add(9, FCharacterLevels{ 300, 150, 500, 1100, 0, 100, 50 });
	Levels.Add(10, FCharacterLevels{ 300, 150, 500, 1200, 0, 100, 50 });
	Levels.Add(11, FCharacterLevels{ 300, 150, 500, 1300, 0, 100, 50 });
	DeathTime = 1.8;
	AwarenessDistance = 2000;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Units/Enemies/Lich/Meshes/OneMeshCharacter/SK_Lich.SK_Lich'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Enemies/Lich/Animations/Lich_Mage_Animation_BP.Lich_Mage_Animation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMont(TEXT("AnimMontage'/Game/Units/Enemies/Lich/Animations/Lich_Mage_Attack_Montage.Lich_Mage_Attack_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialMont(TEXT("AnimMontage'/Game/Units/Enemies/Lich/Animations/Lich_Mage_Special_Montage.Lich_Mage_Special_Montage'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Phase1Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/Lich/Materials/Instances/MI_Lich_Purple.MI_Lich_Purple'"));
	if (Phase1Material.Succeeded()) PhaseMaterials.Add(Phase1Material.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Phase2Material(TEXT("MaterialInstanceConstant'/Game/Units/Enemies/Lich/Materials/Instances/MI_Lich_Ghost.MI_Lich_Ghost'"));
	if (Phase2Material.Succeeded()) PhaseMaterials.Add(Phase2Material.Object);
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
	MinionTypes.Add(AEnemy_Skeleton_Warrior::StaticClass());
	MinionTypes.Add(AEnemy_Skeleton_Archer::StaticClass());
	AIControllerClass = ABasic_Enemy_Controller::StaticClass();
	SetActorScale3D(FVector(3));
	//DropTable.Add(FLoot{ 1, AItem_Wooden_Pickaxe::StaticClass() });
	DropTable.Add(FLoot{ 10, nullptr });

	CapsuleRadiusMultiplier = 0.5f;
}


void AEnemy_Lich_Mage::SpecialAttack()
{
	ResupplyMinions();
	Super::SpecialAttack();
}

void AEnemy_Lich_Mage::CalculateDamage(int BaseAdditionalDamage, float AdditionalDamageMultiplier) {
	Super::CalculateDamage(BaseAdditionalDamage, AdditionalDamageMultiplier);
}

void AEnemy_Lich_Mage::TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage)
{
	if (CurrentPhase == LichMagePhase::Etheral) {
		if (FMath::RandRange(0, 20) == 0) ChangePhase(0);
		Super::TakeDamage(AttackingActor, AmountOfDamage * -1, TypeDamage);
	}
	else{ 
		if (FMath::RandRange(0, 20) == 0) ChangePhase(1);
		Super::TakeDamage(AttackingActor, AmountOfDamage, TypeDamage);
	}
}

void AEnemy_Lich_Mage::ChangePhase(int NewPhase)
{
	switch (NewPhase) {
	case 0:
		CurrentPhase = LichMagePhase::Normal;
		break;
	case 1:
		CurrentPhase = LichMagePhase::Etheral;
		break;
	default:
		break;
	}
	GetMesh()->SetMaterial(0, PhaseMaterials[(int)CurrentPhase]);
}


void AEnemy_Lich_Mage::SetSelected() {
	Super::SetSelected();
	if (CurrentPhase == LichMagePhase::Etheral) ChangePhase(0);
}

void AEnemy_Lich_Mage::SpawnMinions(int Number)
{
	if (MinionTypes.Num() > 0) {
		for (int i = 0; i < Number; i++) {
			auto Vector = FMath::VRand();
			Vector *= FMath::RandRange(0, 500);
			Vector += this->GetActorLocation();
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			ACharacterActor* SpawnedActorRef = GetWorld()->SpawnActor<ACharacterActor>(MinionTypes[FMath::RandRange(0, MinionTypes.Num()-1)], FVector(Vector.X, Vector.Y, 150), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			SpawnedActorRef->SpawnInit(nullptr, Level);
			SpawnedMinions.Add(SpawnedActorRef);
		}
	}
}

void AEnemy_Lich_Mage::ResupplyMinions()
{
	int CurrentMinionsCount = 0;
	for (int i = 0; i < SpawnedMinions.Num(); i++) {
		if (SpawnedMinions[i] && !SpawnedMinions[i]->IsPendingKill()) {
			CurrentMinionsCount++;
		}
	}
	SpawnMinions(MaxMinionSpawns - CurrentMinionsCount);
}
