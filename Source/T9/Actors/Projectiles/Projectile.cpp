// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/Actors/Buildings/DefensiveBuildingActor.h"
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
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
}


void AProjectile::ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay) {
	Target = TargetActor;
	Damage = AttackDamage;
	Spawner = SpawnActor;
	ProjectileMovementDelay = ProjectileDelay;
	BuildingSpawn = Cast<ADefensiveBuildingActor>(Spawner);
	if (BuildingSpawn) ProjectileSpawn = BuildingSpawn->ProjectileSpawn;
	if (ProjectileMovementDelay > 0) {
		FTimerDelegate TickDelay;
		TickDelay.BindUFunction(this, FName("ToggleActive"), true);
		GetWorldTimerManager().SetTimer(ProjectileMovementDelayHandle, TickDelay, ProjectileMovementDelay, false, ProjectileMovementDelay);
	}
	else Active = true;
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Target) {
		IDamageInterface* Enemy = Cast<IDamageInterface>(Target);
		if(Enemy != nullptr) Enemy->TakeDamage(this, Damage);
		this->Destroy();
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ((Target != nullptr) && (Target->IsValidLowLevel())&& (!Target->IsPendingKill())) {
		if (Active) {
			UE_LOG(LogTemp, Warning, TEXT("00000"));
			FVector Direction = (Target->GetActorLocation() - GetActorLocation() + FVector(0, 0, Target->GetSimpleCollisionHalfHeight())).GetSafeNormal();
			ProjectileMovement->Velocity += Direction * 50000.f * DeltaTime;
			ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * ProjectileSpeed * 1000;
		}
		else if(BuildingSpawn) {
			if (BuildingSpawn->Type == Turret) {
				UE_LOG(LogTemp, Warning, TEXT("Turret"));
				SetActorLocation(ProjectileSpawn->GetComponentLocation());
				SetActorRelativeRotation(BuildingSpawn->TurretRotation);
			}
			else if (BuildingSpawn->Type == Character) {
				UE_LOG(LogTemp, Warning, TEXT("Character"));
				if(USkeletalMeshComponent* SpawnCharacter = BuildingSpawn->BuildingDefender) SetActorLocation(SpawnCharacter->GetSocketLocation("hand_r"));
			}
		}
	}
	else this->Destroy();

}

void AProjectile::ToggleActive(bool Input) {
	Active = Input;
}

// Called to bind functionality to input

