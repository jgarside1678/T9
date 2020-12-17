// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Wolf.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AEnemy_Wolf : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	AEnemy_Wolf(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		TArray<class UMaterialInstance*> MeshMaterials;

	//virtual void Attack(AActor* Target) override;

	//virtual void SpecialAttack(AActor* Target) override;
};
