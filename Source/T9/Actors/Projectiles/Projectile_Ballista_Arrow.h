// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DirectionalProjectile.h"
#include "Projectile_Ballista_Arrow.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AProjectile_Ballista_Arrow : public ADirectionalProjectile
{
	GENERATED_BODY()
public:
	AProjectile_Ballista_Arrow(const FObjectInitializer& ObjectInitializer);
};
