// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrackingProjectile.h"
#include "Projectile_Magic_Fire.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AProjectile_Magic_Fire : public ATrackingProjectile
{
	GENERATED_BODY()

public:
	AProjectile_Magic_Fire(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	virtual void BeginPlay() override;
};
