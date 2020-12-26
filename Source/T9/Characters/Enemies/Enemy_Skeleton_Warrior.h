// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Skeleton_Warrior.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AEnemy_Skeleton_Warrior : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEnemy_Skeleton_Warrior(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		TArray<class UMaterialInstance*> MeshMaterials;
};
