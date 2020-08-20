// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

UENUM(BlueprintType)
enum DamageType
{
	All UMETA(DisplayName = "All"),
	Alliance UMETA(DisplayName = "Alliance"),
	Enemy UMETA(DisplayName = "Enemy")
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class T9_API IDamageInterface
{
	GENERATED_BODY()

public:

	UFUNCTION()
	   virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeOfDamage = All);


	UFUNCTION()
		virtual void DamageEnemy(AActor* Actor, float AmountOfDamage);


	UFUNCTION()
		virtual bool CheckIfDead();

	UFUNCTION()
		virtual bool IsDamageable();


	UFUNCTION()
		virtual DamageType GetDamageType();

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
