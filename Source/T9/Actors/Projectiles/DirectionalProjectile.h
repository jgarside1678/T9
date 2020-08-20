// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "DirectionalProjectile.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ADirectionalProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	ADirectionalProjectile(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY()
		FVector ProjectileDirection;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void ToggleActive(bool Input) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay = 0, DamageType DamageActors = Enemy) override;

};
