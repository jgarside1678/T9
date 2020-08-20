// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DirectionalProjectile.h"
#include "Projectile_Arrow.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AProjectile_Arrow : public ADirectionalProjectile
{
	GENERATED_BODY()
public:
	AProjectile_Arrow(const FObjectInitializer& ObjectInitializer);
};
