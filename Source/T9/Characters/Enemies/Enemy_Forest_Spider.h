// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Forest_Spider.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AEnemy_Forest_Spider : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	AEnemy_Forest_Spider(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		TArray<class UMaterialInstance*> MeshMaterials;
};
