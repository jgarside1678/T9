// Fill out your copyright notice in the Description page of Project Settings.
#include "DefensiveBuildingActor.h"
#include "EnemyCharacter.h"
#include "DamageInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "AllianceCharacter.h"

ADefensiveBuildingActor::ADefensiveBuildingActor() {
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(StaticMeshComponent);
}

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
	if (Target != nullptr && !Target->IsPendingKill()) {
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		FActorSpawnParameters SpawnParams;
		FVector Location = GetActorLocation() + ProjectileSpawn->GetComponentLocation();
		if (Projectile) {
			if (!TargetInterface->CheckIfDead()) {
				AProjectile* SpawnedActorRef = GetWorld()->SpawnActor<AProjectile>(Projectile, Location, ProjectileSpawn->GetComponentRotation(), SpawnParams);
				SpawnedActorRef->ProjectileInnit(Target, GetDamage(), this, ProjectileDelay);
			}
		}
		else TargetInterface->DamageEnemy(Target, GetDamage());

		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ADefensiveBuildingActor::AttackTarget, Upgrades[Level].Attack.AttackSpeed, false, Upgrades[Level].Attack.AttackSpeed);
	}
	else SetTarget();
}

void ADefensiveBuildingActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (Target && TurretStaticMeshComponent) {
		FVector AimLocation = Target->GetActorLocation() + FVector(0, 0, 150);
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(TurretStaticMeshComponent->GetComponentLocation(), AimLocation);
		TurretRotation = UKismetMathLibrary::RInterpTo(TurretStaticMeshComponent->GetComponentRotation(), Rot, DeltaTime, 3) - GetActorRotation();
		TurretStaticMeshComponent->SetRelativeRotation(TurretRotation);
		ProjectileSpawn->SetRelativeRotation(TurretRotation);
	}
	else if (Target && BuildingDefender) {
		FVector AimLocation = Target->GetActorLocation() + FVector(0, 0, 150);
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(BuildingDefender->GetActorLocation(), AimLocation);
		TurretRotation = UKismetMathLibrary::RInterpTo(BuildingDefender->GetActorRotation(), Rot, DeltaTime, 3) - GetActorRotation();
		BuildingDefender->SetActorRotation(TurretRotation);
		ProjectileSpawn->SetRelativeRotation(FRotator(0,0, TurretRotation.Yaw));
	}
}



