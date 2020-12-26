// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Projectiles/Projectile.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"
#include "DefensiveBuildingActor.generated.h"


UENUM()
    enum TargetPiority { Closest, HighestHP, LowestHP, Random };

UENUM()
    enum TowerType { Turret, Character, Default };


UCLASS()
class T9_API ADefensiveBuildingActor : public ABuildingActor
{
	GENERATED_BODY()

public:

	ADefensiveBuildingActor();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		class USceneComponent* ProjectileSpawn;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics")
		FRotator TurretRotation;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics")
		TEnumAsByte<TowerType> Type = Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		class USkeletalMeshComponent* BuildingDefender;

    UFUNCTION(BlueprintCallable, Category = "Mesh Merge", meta = (UnsafeDuringActorConstruction = "true"))
        static class USkeletalMesh* MergeMeshes(const FSkeletalMeshMergeParams& Params);


protected:

	FTimerHandle AttackTimerHandle;

	virtual void BeginPlay() override;

	virtual void SetTarget(AActor* NewTarget = nullptr) override;

	virtual void CalculateAttackSpeed() override;

	UPROPERTY()
	   TSubclassOf<AProjectile> Projectile;

	UPROPERTY()
		TEnumAsByte<TargetPiority> AttackPiority = Closest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		int AttackStreak = 0;

	UPROPERTY()
		FRotator ProjectileSpawnRotation = FRotator(0, 0, 0);

	UPROPERTY()
		float ProjectileDelay = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TurretStaticMeshComponent;

	UPROPERTY(EditAnywhere)
		TArray<USkeletalMesh*> MeshPeices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		class USceneComponent* DefenderDisplacement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		class UAnimMontage* DefenderAttackAnimation;

	UFUNCTION()
	   virtual void AttackTarget();

    UFUNCTION()
        void MeshInit();


};








