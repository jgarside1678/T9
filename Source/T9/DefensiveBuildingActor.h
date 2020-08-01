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

	UPROPERTY()
		class USceneComponent* ProjectileSpawn;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		FRotator TurretRotation;

protected:
	ADefensiveBuildingActor();

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
		FRotator ProjectileSpawnRotation = FRotator(0, 0, 0);

	UPROPERTY()
		float ProjectileDelay = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TurretStaticMeshComponent;
};
