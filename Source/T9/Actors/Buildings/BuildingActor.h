// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/Interfaces/SelectInterface.h"
#include "BuildingActor.generated.h"



USTRUCT(BlueprintType)
struct FBuildingCosts {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Wood = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Stone = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Food = 0;
};

USTRUCT(BlueprintType)
struct FBuildingProduction {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Wood = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Stone = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Food = 0;
};

USTRUCT(BlueprintType)
struct FBuildingAttack {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackSpeed = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackRangeMultipler = 1;
};

USTRUCT(BlueprintType)
struct FBuildingUpgrades {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float XP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PowerRating = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBuildingCosts Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBuildingAttack Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBuildingProduction Production;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* BaseMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* TurretMesh = nullptr;
};



UCLASS()
class T9_API ABuildingActor : public AActor, public IDamageInterface, public ISelectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildingActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	    virtual void SetTarget();

	UPROPERTY()
		class AActor* Target;

	UFUNCTION(BlueprintCallable)
		virtual void Upgrade();

	UPROPERTY()
		UParticleSystem* UpgradeParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		FString BuildingName = "Building";

	UPROPERTY(VisibleAnywhere, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		TMap<int32, FBuildingUpgrades> Upgrades;

	UPROPERTY(VisibleAnywhere, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float TotalCost;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		class AGameGridActor* Grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class USceneComponent* MeshDisplacement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BuildingRangeCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		int BuildingDetectionRange = 3;

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		class UAudioComponent* UpgradeAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		bool Disabled = false;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY()
		FVector BuildingExtent;

	UFUNCTION(Category = "Building Basics")
		int GetBuildingCount();

	UFUNCTION(Category = "Building Basics")
		int GetMaxBuildingCount();

	//For initalising spawn arguments
	UFUNCTION()
		void BuildingInnit(AGameGridActor* BuildingGrid, FVector BuildingCenterLocation, FVector BuildingCornerLocation, int Rotation);

	UPROPERTY()
		int GridRotation;

	UPROPERTY()
		FVector BuildingCenterLocation;

	UPROPERTY()
		FVector BuildingCornerLocation;

	UPROPERTY()
		FVector2D GridLength = FVector2D(1);

	UFUNCTION(BlueprintCallable)
		void GetBuildingRangeCollider(FVector& Origin, FVector& BoxExtent);

	UFUNCTION(BlueprintCallable)
		class UStaticMeshComponent* GetStaticMeshComp();

	UFUNCTION()
		virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage);

	UFUNCTION()
		virtual void DamageEnemy(AActor* Actor, float AmountOfDamage);

	UFUNCTION(BlueprintCallable)
		void RemoveBuilding();

	UFUNCTION(BlueprintCallable)
		void SetMaxHealth(float Number);

	UFUNCTION(BlueprintCallable)
		void SetCurrentHealth(float Number);

	UFUNCTION(BlueprintCallable)
		void IncreaseMaxHealth(float Number);

	UFUNCTION(BlueprintCallable)
		void ResetHealth();

	UPROPERTY()
		int OutlineColour = 2;

	UFUNCTION()
		virtual void SetSelected();

	UFUNCTION()
		virtual void SetUnSelected();

	UFUNCTION(BlueprintCallable)
		float GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
		float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
		FString GetName();

	UFUNCTION(BlueprintCallable)
		int GetLevel();

	UFUNCTION()
		FBuildingCosts GetCost();

	UFUNCTION(BlueprintCallable)
		float GetBuildXP();

	UFUNCTION(BlueprintCallable)
	    float GetDamage();

	UPROPERTY()
		bool IsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GridSpace;

};

