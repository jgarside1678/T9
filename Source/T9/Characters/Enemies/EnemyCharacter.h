// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/CharacterActor.h"
#include "AI/Navigation/NavigationAvoidanceTypes.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */


static FNavAvoidanceMask EnemyGroup;

USTRUCT()
struct FLoot {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int LootChance = 0;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> ItemClass;
};

UCLASS()
class T9_API AEnemyCharacter : public ACharacterActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DeathInit();

	UPROPERTY()
		TArray<FLoot> DropTable;

	virtual void GenerateLoot();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
