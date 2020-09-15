// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Lava_Elemental.generated.h"

/**
 * 
 */

UENUM()
enum LavaElementalPhase
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
		TEnumAsByte<LavaElementalPhase> CurrentPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
		TArray<class UMaterialInstance*> PhaseMaterials;

	virtual void Attack(AActor* Target) override;

	virtual void SpecialAttack(AActor* Target) override;

	virtual void CalculateDamage(int BaseAdditionalDamage) override;
};
