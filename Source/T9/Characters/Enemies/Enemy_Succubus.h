// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Enemy_Succubus.generated.h"

/**
 * 
 */


UENUM()
enum SuccubusPhase
{
	Normal UMETA(DisplayName = "Normal"),
	Flying UMETA(DisplayName = "Flying"),
	Channelling UMETA(DisplayName = "Channelling")
};

UCLASS()
class T9_API AEnemy_Succubus : public AEnemyCharacter
{
	GENERATED_BODY()
public :
	AEnemy_Succubus(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase")
		TEnumAsByte<SuccubusPhase> CurrentPhase;

protected:

	virtual void SpecialAttack() override;

	virtual void CalculateDamage(int BaseAdditionalDamage = 0, float AdditionalDamageMultiplier = 1) override;

	void FlyingHeal();

	FTimerHandle FlyingHealHandle;
};
