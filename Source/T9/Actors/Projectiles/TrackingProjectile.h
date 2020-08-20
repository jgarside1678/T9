// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Projectiles/Projectile.h"
#include "TrackingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ATrackingProjectile : public AProjectile
{
	GENERATED_BODY()
public:
	ATrackingProjectile(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay = 0, DamageType DamageActors = Enemy) override;


};
