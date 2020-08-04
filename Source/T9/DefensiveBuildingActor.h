// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "BuildingActor.h"
#include "AllianceCharacter.h"
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

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		class USceneComponent* ProjectileSpawn;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		FRotator TurretRotation;


	UPROPERTY()
		TEnumAsByte<TowerType> Type = Default;


    UFUNCTION(BlueprintCallable, Category = "Mesh Merge", meta = (UnsafeDuringActorConstruction = "true"))
        static class USkeletalMesh* MergeMeshes(const FSkeletalMeshMergeParams& Params);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		class USkeletalMeshComponent* BuildingDefender;

protected:
	ADefensiveBuildingActor();

	class IDamageInterface* TargetInterface;

	virtual void BeginPlay() override;

	FTimerHandle AttackTimerHandle;

	UPROPERTY()
	   TSubclassOf<AProjectile> Projectile;

	UPROPERTY()
		TEnumAsByte<TargetPiority> AttackPiority = Closest;

	virtual void SetTarget();

	UFUNCTION()
	   virtual void AttackTarget();

	UPROPERTY()
		FRotator ProjectileSpawnRotation = FRotator(0, 0, 0);

	UPROPERTY()
		float ProjectileDelay = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TurretStaticMeshComponent;


    UPROPERTY(EditAnywhere)
        TArray<USkeletalMesh*> MeshPeices;

    UFUNCTION()
        void MeshInit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		FVector DefenderDisplacement = FVector(0);

};








