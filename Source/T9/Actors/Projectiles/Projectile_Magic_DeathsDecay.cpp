// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Magic_DeathsDecay.h"
#include "NiagaraSystem.h"
#include "T9/Interfaces/DamageInterface.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/PrimitiveComponent.h"

AProjectile_Magic_DeathsDecay::AProjectile_Magic_DeathsDecay(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	ProjectileSpeed = 3;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Particle(TEXT("NiagaraSystem'/Game/Particles/MagicProjectiles/Niagara/Poison/NS_Poison_Trail.NS_Poison_Trail'"));
	if (Particle.Succeeded()) ParticleEffect = Particle.Object;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Explosion(TEXT("NiagaraSystem'/Game/Particles/MagicProjectiles/Niagara/Poison/NS_Poison_Impact.NS_Poison_Impact'"));
	if (Explosion.Succeeded()) ExplosionEffect = Explosion.Object;
}

void AProjectile_Magic_DeathsDecay::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Active && ExplosionEffect) UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionEffect, Target->GetRootComponent(), FName("Explosion"), FVector(0, 0, 0), FRotator(0), EAttachLocation::SnapToTarget, true);
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,  SweepResult);
}

void AProjectile_Magic_DeathsDecay::BeginPlay() {
	Super::BeginPlay();
	if (ParticleEffect) UNiagaraFunctionLibrary::SpawnSystemAttached(ParticleEffect, BoxCollider, FName(""), FVector(0, 0, 0), FRotator(0), EAttachLocation::SnapToTarget, false);
}
