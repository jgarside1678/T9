// Fill out your copyright notice in the Description page of Project Settings.
#include "DefensiveBuildingActor.h"
#include "EnemyCharacter.h"
#include "DamageInterface.h"
#include "TimerManager.h"

void ADefensiveBuildingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADefensiveBuildingActor::SetTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("Set Target Called"));
	TArray<AActor*> CollidingActors;
	GetOverlappingActors(CollidingActors, AEnemyCharacter::StaticClass());
	if ((Target == nullptr && CollidingActors.Num() > 0 && this->IsDead == false) || (Target->IsValidLowLevel() && Target->IsPendingKill() && CollidingActors.Num() > 0) && this->IsDead == false) {
		switch (AttackPiority) {
		case Closest:
			float ClosestDistance;
			for (int x = 0; x < CollidingActors.Num(); x++) {
				float Distance = (GetActorLocation() - CollidingActors[x]->GetActorLocation()).Size();
				if (Target == nullptr || Distance < ClosestDistance || Target->IsPendingKill()) {
					ClosestDistance = Distance;
					Target = CollidingActors[x];
				}
			}
			break;
		case HighestHP:
			UE_LOG(LogTemp, Warning, TEXT("Target Method Not Implemented Yet"));
			break;
		case LowestHP:
			UE_LOG(LogTemp, Warning, TEXT("Target Method Not Implemented Yet"));
			break;
		case Random:
			UE_LOG(LogTemp, Warning, TEXT("Target Method Not Implemented Yet"));
			break;
		default:
			break;
		}
		UE_LOG(LogTemp, Warning, TEXT("New Target"));
		TargetInterface = Cast<IDamageInterface>(Target);
		AttackTarget();
	}
}

void ADefensiveBuildingActor::AttackTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack Target Called"));
	if (Target != nullptr && !Target->IsPendingKill()) {
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		FActorSpawnParameters SpawnParams;
		FVector Location = GetActorLocation() + ProjectileSpawnLocation;
		if (Projectile) {
			if (!TargetInterface->CheckIfDead()) {
				AProjectile* SpawnedActorRef = GetWorld()->SpawnActor<AProjectile>(Projectile, Location, ProjectileSpawnRotation, SpawnParams);
				SpawnedActorRef->ProjectileInnit(Target, GetDamage(), ProjectileDelay);
			}
		}
		else TargetInterface->DamageEnemy(Target, GetDamage());

		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ADefensiveBuildingActor::AttackTarget, Upgrades[Level].Attack.AttackSpeed, false, Upgrades[Level].Attack.AttackSpeed);
	}
	else SetTarget();
}

void ADefensiveBuildingActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}



