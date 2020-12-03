// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Lich_Mage.generated.h"

/**
 * 
 */
UENUM()
enum class LichMagePhase
{
	Normal UMETA(DisplayName = "Normal"),
	Etheral UMETA(DisplayName = "Etheral")
};


UCLASS()
class T9_API AEnemy_Lich_Mage : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEnemy_Lich_Mage(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
		LichMagePhase CurrentPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
		TArray<class UMaterialInstance*> PhaseMaterials;

	virtual void Attack(AActor* Target) override;

	virtual void SpecialAttack(AActor* Target) override;

	virtual void CalculateDamage(int BaseAdditionalDamage = 0, float AdditionalDamageMultiplier = 1) override;

	virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage) override;

	virtual void ChangePhase(int NewPhase = -1) override;

	virtual void SetSelected() override;
};
