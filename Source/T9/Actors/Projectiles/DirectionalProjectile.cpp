// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/Actors/Buildings/DefensiveBuildingActor.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"

ADirectionalProjectile::ADirectionalProjectile(const FObjectInitializer& ObjectInitializer) {

}



void ADirectionalProjectile::ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay, DamageType DamageActors){
	Super::ProjectileInnit(TargetActor, AttackDamage, SpawnActor, ProjectileDelay, DamageActors);
	ProjectileDirection = (Target->GetActorLocation() - GetActorLocation() + FVector(0, 0, Target->GetSimpleCollisionHalfHeight())).GetSafeNormal();
}

void ADirectionalProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


void ADirectionalProjectile::ToggleActive(bool Input) {
	ProjectileDirection = (Target->GetActorLocation() - GetActorLocation() + FVector(0, 0, Target->GetSimpleCollisionHalfHeight())).GetSafeNormal();
	Super::ToggleActive(Input);
}

// Called every frame
void ADirectionalProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ((Target != nullptr) && (Target->IsValidLowLevel()) && (!Target->IsPendingKill())) {
		if (Active) {
			ProjectileMovement->Velocity = ProjectileDirection * 1000 * ProjectileSpeed;
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