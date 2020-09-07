// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "Resource_Food.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AResource_Food : public AResourceActor
{
	GENERATED_BODY()
public:
	AResource_Food();

protected:

	FTimerHandle ResourceSpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		int MaxSpawnCount = 1;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		int CurrentSpawnCount = 0;


	UPROPERTY(EditAnywhere, Category = "Spawning")
		float SpawnTime = 10.0f;

	UFUNCTION()
		ACharacter* Spawn();

	UPROPERTY()
		bool AutoSpawning = false;

	UFUNCTION()
		void AutoRespawn();

	UFUNCTION()
		void Respawn();

	virtual void ResourceInit(class AGameGridActor* Grid, TEnumAsByte<Tiers> StartingResourceTier = Tier1) override;

	UFUNCTION()
		void KillAll();

private:
};
