// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackingProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/Actors/Buildings/DefensiveBuildingActor.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"

ATrackingProjectile::ATrackingProjectile(const FObjectInitializer& ObjectInitializer) {

}

void ATrackingProjectile::ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay, DamageType DamageActors){
	Super::ProjectileInnit(TargetActor, AttackDamage, SpawnActor, ProjectileDelay, DamageActors);
}

void ATrackingProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

// Called every frame
void ATrackingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ((Target != nullptr) && (Target->IsValidLowLevel()) && (!Target->IsPendingKill())) {
		if (Active) {
			FVector Direction = (Target->GetActorLocation() - GetActorLocation() + FVector(0, 0, Target->GetSimpleCollisionHalfHeight())).GetSafeNormal();
			ProjectileMovement->Velocity += Direction * 50000.f * DeltaTime;
			ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * ProjectileSpeed * 1000;
		}
		else if (BuildingSpawn) {
			if (BuildingSpawn->Type == Turret) {
				SetActorLocation(ProjectileSpawn->GetComponentLocation());
				SetActorRelativeRotation(BuildingSpawn->TurretRotation);
			}
			else if (BuildingSpawn->Type == Character) {
				if (USkeletalMeshComponent* SpawnCharacter = BuildingSpawn->BuildingDefender) SetActorLocation(SpawnCharacter->GetSocketLocation("hand_r"));
			}
		}
	}
	else this->Destroy();

}