// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "BuildingActor.h"
#include "DefensiveBuildingActor.generated.h"

/**
 * 
 */
UENUM()
    enum TargetPiority { Closest, HighestHP, LowestHP, Random };


UCLASS()
class T9_API ADefensiveBuildingActor : public ABuildingActor
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

protected:

	class IDamageInterface* TargetInterface;

	virtual void BeginPlay() override;

	FTimerHandle AttackTimerHandle;

	UPROPERTY()
	   TSubclassOf<AProjectile> Projectile;

	UPROPERTY()
		TEnumAsByte<TargetPiority> AttackPiority = Closest;

	virtual void SetTarget();

	UFUNCTION()
	   void AttackTarget();

	UPROPERTY()
		FVector ProjectileSpawnLocation = FVector(0,0,100);

	UPROPERTY()
		FRotator ProjectileSpawnRotation = FRotator(0, 0, 0);

	UPROPERTY()
		float ProjectileDelay = 0.0f;
};
