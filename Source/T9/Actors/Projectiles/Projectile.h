// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "T9/Interfaces/DamageInterface.h"
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

	FTimerHandle ProjectileLifeTimeHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<DamageType> DamageActorsOfType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles", Meta = (AllowPrivateAccess = "true"))
		class UNiagaraSystem* ParticleEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles", Meta = (AllowPrivateAccess = "true"))
		class UNiagaraSystem* ExplosionEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		float ProjectileLifeTime = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
	    float ProjectileMovementDelay = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		float ProjectileSpeed = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		class UPrimitiveComponent* ProjectilePrimitive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		class AActor* Spawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		class ADefensiveBuildingActor* BuildingSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		class USceneComponent* ProjectileSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Basics")
		bool Active = false;

	UFUNCTION()
		virtual void ToggleActive(bool Input);

	UFUNCTION()
		virtual void ProjectileExplode();

	UFUNCTION()
		virtual void ProjectileDestroy();

	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	    virtual void ProjectileInnit(AActor* TargetActor, float AttackDamage, AActor* SpawnActor, float ProjectileDelay = 0, DamageType DamageActors = Enemy);

	UFUNCTION()
		class ADefensiveBuildingActor* GetSpawnBuilding();


};
