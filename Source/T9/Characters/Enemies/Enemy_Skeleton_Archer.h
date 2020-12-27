// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "Enemy_Skeleton_Archer.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AEnemy_Skeleton_Archer : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEnemy_Skeleton_Archer(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		TArray<class UMaterialInstance*> MeshMaterialsBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		TArray<class UMaterialInstance*> MeshMaterialsArmour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		TArray<class UMaterialInstance*> MeshMaterialsBow;
};
