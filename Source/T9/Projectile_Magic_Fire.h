// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Projectile_Magic_Fire.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AProjectile_Magic_Fire : public AProjectile
{
	GENERATED_BODY()

public:
	AProjectile_Magic_Fire(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		class UNiagaraSystem* ParticleEffect;


	virtual void BeginPlay() override;
};
