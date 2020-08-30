// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Lich_Mage.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AEnemy_Lich_Mage : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEnemy_Lich_Mage(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void Attack(AActor* Target) override;

	virtual void SpecialAttack(AActor* Target) override;

	virtual void CalculateDamage(int BaseAdditionalDamage) override;
};
