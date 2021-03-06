// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Lava_Elemental.generated.h"

/**
 * 
 */

UENUM()
enum class LavaElementalPhase
{
	Red UMETA(DisplayName = "Red"),
	Cyan UMETA(DisplayName = "Cyan"),
	Gold UMETA(DisplayName = "Gold"),
	Green UMETA(DisplayName = "Green"),
	Purple UMETA(DisplayName = "Purple")
};


UCLASS()
class T9_API AEnemy_Lava_Elemental : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEnemy_Lava_Elemental(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	    TEnumAsByte<LavaElementalPhase> GetCurrentPhase();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
		LavaElementalPhase CurrentPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
		TArray<class UMaterialInstance*> PhaseMaterials;


	virtual void SpecialAttack() override;

	virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage) override;

	virtual void ChangePhase(int NewPhase = -1) override;

	virtual void CalculateDamage(int BaseAdditionalDamage = 0, float AdditionalDamageMultiplier = 1) override;
};
