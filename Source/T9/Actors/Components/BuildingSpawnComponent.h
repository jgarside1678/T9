// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingSpawnComponent.generated.h"

UENUM()
enum SpawnMethods
{
	SurroundingBuilding UMETA(DisplayName = "SurroundingBuilding"),
	PointSpawn UMETA(DisplayName = "PointSpawn"),
	RandomNearPointSpawn UMETA(DisplayName = "RandomNearPointSpawn")
};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class T9_API UBuildingSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingSpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;

public:	

	FVector BoxExtent;
	FVector Origin;
	float BuildingX;
	float BuildingY;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float RandomFloat(float a, float b);

	FTimerHandle RespawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TEnumAsByte<SpawnMethods> SpawnMethod = SurroundingBuilding;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TArray<AActor*> ActorsSpawned;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		float SpawnTime = 10.0f;

	UPROPERTY(EditAnywhere, Category="Spawning")
		int MaxSpawnCount = 1;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	    int CurrentSpawnCount = 0;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		float MaxSpawnRange = 100;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		ESpawnActorCollisionHandlingMethod SpawnParamCollision = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	UPROPERTY()
		class AActor* MyOwner;

	UPROPERTY()
		class ABuildingActor* OwningBuilding;

	UPROPERTY()
		float YAxis;

	UPROPERTY()
		float XAxis;

	UFUNCTION()
		AActor* Spawn();

	UPROPERTY()
		bool AutoSpawning = false;

	UFUNCTION()
		void AutoRespawn();

	UFUNCTION()
		void Respawn();

	UFUNCTION()
		void Init();

	UFUNCTION()
		void UpdateSpawnedCharacters();

	FTimerHandle SpawnTimerHandle;

	UFUNCTION()
		void RandomSpawnLocation();

	UFUNCTION()
		void KillAll();
		
};