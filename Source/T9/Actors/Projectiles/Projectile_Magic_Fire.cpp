// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Magic_Fire.h"
#include "NiagaraSystem.h"
#include "T9/Interfaces/DamageInterface.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/PrimitiveComponent.h"

AProjectile_Magic_Fire::AProjectile_Magic_Fire(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	ProjectileSpeed = 3;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Particle(TEXT("NiagaraSystem'/Game/Particles/sA_Projectilevfx/Vfx/Fx/Niagara_Systems/NS_Projectile2_Small.NS_Projectile2_Small'"));
	if (Particle.Succeeded()) ParticleEffect = Particle.Object;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Explosion(TEXT("NiagaraSystem'/Game/Particles/sA_Projectilevfx/Vfx/Fx/Niagara_Systems/NS_Hit2.NS_Hit2'"));
	if(Explosion.Succeeded()) ExplosionEffect = Explosion.Object;
}

void AProjectile_Magic_Fire::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageInterface* Enemy = Cast<IDamageInterface>(OtherActor);
	if (Enemy != nullptr) Enemy->TakeDamage(Spawner, Damage, TypeOfDamage);
	if (OtherActor == Target) {
		this->SetActorScale3D(FVector(10));
		ProjectileExplode();
		ProjectileDestroy();
	}

}

void AProjectile_Magic_Fire::BeginPlay() {
	Super::BeginPlay();
	if (ParticleEffect) UNiagaraFunctionLibrary::SpawnSystemAttached(ParticleEffect, BoxCollider, FName(""), FVector(0, 0, 0), FRotator(0), EAttachLocation::SnapToTarget, false);
}