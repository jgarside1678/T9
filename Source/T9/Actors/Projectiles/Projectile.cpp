// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "T9/Interfaces/DamageInterface.h"
#include "NiagaraFunctionLibrary.h"
#include "T9/Actors/Buildings/DefensiveBuildingActor.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"

// Sets default values
AProjectile::AProjectile() :
	StaticMeshComp(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"))),
	ProjectileMovement(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"))),
	BoxCollider(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider")))
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp->SetCanEverAffectNavigation(false);
	RootComponent = BoxCollider;
	StaticMeshComp->SetupAttachment(RootComponent);
	ProjectileMovement->UpdatedComponent = BoxCollider;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bIsHomingProjectile = false;
	ProjectileMovement->HomingAccelerationMagnitude = 0.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->Velocity = FVector(0.f);
	StaticMeshComp->SetCollisionProfileName("NoCollision");
	BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);


	ProjectilePrimitive = Cast<UPrimitiveComponent>(GetComponentByClass(USceneComponent::StaticClass()));
}


void AProjectile::ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay, DamageType DamageActors) {
	Target = TargetActor;
	Damage = AttackDamage;
	DamageActorsOfType = DamageActors;
	Spawner = SpawnActor;
	ProjectileMovementDelay = ProjectileDelay;
	BuildingSpawn = Cast<ADefensiveBuildingActor>(Spawner);
	if (BuildingSpawn) ProjectileSpawn = BuildingSpawn->ProjectileSpawn;
	if (ProjectileMovementDelay > 0) {
		FTimerDelegate TickDelay;
		TickDelay.BindUFunction(this, FName("ToggleActive"), true);
		GetWorldTimerManager().SetTimer(ProjectileMovementDelayHandle, TickDelay, ProjectileMovementDelay, false, ProjectileMovementDelay);
	}
	else {
		Active = true;
		GetWorldTimerManager().SetTimer(ProjectileLifeTimeHandle, this, &AProjectile::ProjectileDestroy, ProjectileLifeTime, false, ProjectileLifeTime);
	}
}

ADefensiveBuildingActor* AProjectile::GetSpawnBuilding()
{
	return BuildingSpawn;
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Active && OtherActor == Target) {
		IDamageInterface* Enemy = Cast<IDamageInterface>(Target);
		if(Enemy != nullptr) Enemy->TakeDamage(Spawner, Damage, DamageActorsOfType);
		ProjectileDestroy();
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::ToggleActive(bool Input) {
	Active = Input;
	if (Active) GetWorldTimerManager().SetTimer(ProjectileLifeTimeHandle, this, &AProjectile::ProjectileDestroy, ProjectileLifeTime, false, ProjectileLifeTime);
	//else GetWorldTimerManager().PauseTimer(ProjectileLifeTimeHandle);
}

void AProjectile::ProjectileExplode()
{
	if (ProjectilePrimitive) {
		if (ExplosionEffect) {
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(Target, ExplosionEffect, GetActorLocation(), FRotator(0), FVector(2), true, true);
			//UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionEffect, Target->GetRootComponent(), FName(""), FVector(0, 0, 0), FRotator(0), EAttachLocation::SnapToTarget, true);
		}
	}
}

void AProjectile::ProjectileDestroy()
{
	this->Destroy();
}

// Called to bind functionality to input

