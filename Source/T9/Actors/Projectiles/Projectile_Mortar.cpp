// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Mortar.h"
#include "Components/BoxComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile_Mortar::AProjectile_Mortar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Explosion(TEXT("NiagaraSystem'/Game/Particles/MagicProjectiles/Niagara/Fire/NS_Fire_Impact.NS_Fire_Impact'"));
	if (Explosion.Succeeded()) ExplosionEffect = Explosion.Object;

	ProjectileSpeed = 1.2;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/SiegeWeaponsPackFullPack/Resources/Projectiles/projectile02.projectile02'"));
	if (Mesh.Succeeded()) {
		StaticMeshComp->SetStaticMesh(Mesh.Object);
		FVector BoxExtent = StaticMeshComp->GetStaticMesh()->GetBoundingBox().GetExtent();
		BoxCollider->SetBoxExtent(BoxExtent);
		StaticMeshComp->SetRelativeLocation(FVector(-BoxExtent.X, 0, 0));
		StaticMeshComp->SetRelativeScale3D(FVector(2));
	}
}

void AProjectile_Mortar::Tick(float DeltaTime)
{
	ProjectileMovement->Velocity = ClimbingDirection * 1000 * ProjectileSpeed;
	ClimbingDirection.Z -= 1100 / TargetDistance * ProjectileSpeed * DeltaTime;
}

void AProjectile_Mortar::ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay, DamageType DamageActors)
{
	Super::ProjectileInnit(TargetActor, AttackDamage, SpawnActor, ProjectileDelay, DamageActors);
}

void AProjectile_Mortar::CalculateTrajectory(AActor* TargetActor)
{
	ClimbingDirection = (ProjectileDirection*0.5) + FVector(0, 0, 1);
	TargetDistance = (FVector2D(Target->GetActorLocation().X, Target->GetActorLocation().Y) - FVector2D(GetActorLocation().X, GetActorLocation().Y)).Size();
}

void AProjectile_Mortar::ToggleActive(bool Input)
{
	Super::ToggleActive(Input);
	CalculateTrajectory(Target);
}



void AProjectile_Mortar::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Active) {
		IDamageInterface* Enemy = Cast<IDamageInterface>(OtherActor);
		if (Enemy != nullptr) Enemy->TakeDamage(this, Damage, DamageActorsOfType);
		if (OtherActor != Spawner && !Exploded) {
			Exploded = true;
			this->SetActorScale3D(FVector(10));
			ProjectileExplode();
			ProjectileDestroy();
		}
	}

}