// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Projectiles/TrackingProjectile.h"
#include "Projectile_Arrow.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AProjectile_Arrow : public ATrackingProjectile
{
	GENERATED_BODY()
public:
	AProjectile_Arrow(const FObjectInitializer& ObjectInitializer);
};
