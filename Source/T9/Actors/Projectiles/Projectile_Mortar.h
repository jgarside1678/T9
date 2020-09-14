// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Projectiles/DirectionalProjectile.h"
#include "Projectile_Mortar.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AProjectile_Mortar : public ADirectionalProjectile
{
	GENERATED_BODY()
public:

	AProjectile_Mortar(const FObjectInitializer& ObjectInitializer);

protected:

	FTimerHandle ProjectileTrajectoryHandle;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay = 0, DamageType DamageActors = Enemy) override;

	virtual void ToggleActive(bool Input) override;

	UFUNCTION()
	    virtual void CalculateTrajectory(AActor* TargetActor);

	//UFUNCTION()
	//    virtual void ToggleClimbing();
 
	UPROPERTY()
		bool Exploded = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		float TargetDistance;

	UPROPERTY()
		FVector ClimbingDirection;
};
