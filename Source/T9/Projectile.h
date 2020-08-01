// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Projectile.generated.h"

UCLASS()
class T9_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AProjectile();

protected:

	UPROPERTY()
	   class AActor* Target;

	UPROPERTY()
	   float Damage;
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	FTimerHandle ProjectileMovementDelayHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	    float ProjectileMovementDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class AActor* Spawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class ADefensiveBuildingActor* BuildingSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USceneComponent* SpawnLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		bool Active = true;

	UFUNCTION()
		void ToggleActive(bool Input);


private:

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	    void ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay = 0);


};
