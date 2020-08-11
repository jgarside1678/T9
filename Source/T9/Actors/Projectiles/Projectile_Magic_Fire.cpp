// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Magic_Fire.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"

AProjectile_Magic_Fire::AProjectile_Magic_Fire(const FObjectInitializer& ObjectInitializer) : Super() {
	ProjectileSpeed = 3;
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> MythicalParticle(TEXT("NiagaraSystem'/Game/Particles/sA_Projectilevfx/Vfx/Fx/Niagara_Systems/NS_Projectile2_Small.NS_Projectile2_Small'"));
	ParticleEffect =  MythicalParticle.Object;
}

void AProjectile_Magic_Fire::BeginPlay() {
	Super::BeginPlay();
	if (ParticleEffect) UNiagaraFunctionLibrary::SpawnSystemAttached(ParticleEffect, BoxCollider, FName(""), FVector(0, 0, 0), FRotator(0), EAttachLocation::SnapToTarget, false);
}