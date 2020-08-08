// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Enemy_Succubus.generated.h"

/**
 * 
 */


UENUM()
enum Phase
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
		TEnumAsByte<Phase> CurrentPhase;

protected:

	void Attack(AActor* Target, int Number = 1);

	void SpecialAttack(AActor* Target, int Number = 1);

	void CalculateDamage();

	void FlyingHeal();

	FTimerHandle FlyingHealHandle;
};
