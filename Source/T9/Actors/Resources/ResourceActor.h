// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T9/Interfaces/SelectInterface.h"
#include "ResourceActor.generated.h"


UENUM()
enum Resources
{
	Wood UMETA(DisplayName = "Wood"),
	Stone UMETA(DisplayName = "Stone"),
	Food UMETA(DisplayName = "Food")
};

UENUM()
enum Tiers
{
	Tier1 UMETA(DisplayName = "Tier1"),
	Tier2 UMETA(DisplayName = "Tier2"),
	Tier3 UMETA(DisplayName = "Tier3")
};

USTRUCT(BlueprintType)
struct FResourceTierStats {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* ResourceMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ACharacter> ResourceSpawnCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ResourceGatherMultiplier = 1;
};


UCLASS()
class T9_API AResourceActor : public AActor, public ISelectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		TEnumAsByte<Resources> ResourceType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource Static Meshs", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<Tiers> Tier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource Static Meshs", Meta = (AllowPrivateAccess = "true"))
		TArray<ACharacter*> ResourceSpawns;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource Static Meshs", Meta = (AllowPrivateAccess = "true"))
		class UInstancedStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource Box Collider", Meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
	//	FString Name = "Resource";

	UPROPERTY()
	    TArray<UStaticMeshComponent*> Meshs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		TMap<TEnumAsByte<Tiers>, FResourceTierStats> ResourceTiers;

	UPROPERTY()
		int OutlineColour = 3;

	UPROPERTY()
		FVector BoxExtentMultiplier = FVector(1);

	//Resource Widgets

	UPROPERTY()
		float ResourceSelectHeight = 200.0f;

	UPROPERTY()
		class UWidgetComponent* ResourceQuickSelectComponent;

	UPROPERTY()
		TSubclassOf<UUserWidget> ResourceQuickSelectClass = nullptr;

	UPROPERTY()
		class UResourceQuickSelect* ResourceQuickSelect;

	FTimerHandle ResourceSpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		int MaxSpawnCount = 1;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		int CurrentSpawnCount = 0;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		float SpawnTime = 10.0f;


public:	
	// Called every frame
	UPROPERTY()
		FVector CollectionDistance = FVector(100);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	    void GetClosestStaticMesh(FVector Location, FVector& ClosestMeshLocation, FVector& ClosestMeshBounds);

	UFUNCTION()
		void GetClosestSpawnedCharacter(FVector Location, class AResourceCharacter*& ClosestCharacter);

	UFUNCTION()
		virtual void SetSelected() override;

	UFUNCTION()
		virtual void SetUnSelected() override;

	UFUNCTION(BlueprintCallable)
		virtual FString GetName() override;

	UFUNCTION(BlueprintCallable)
		struct FResourceTierStats GetResourceStats();

	UFUNCTION(BlueprintCallable)
		int GetTier();

	UFUNCTION(BlueprintCallable)
		int GetSpawnedUnits();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GridSpace;

	UFUNCTION()
		virtual void ResourceInit(class AGameGridActor* Grid, TEnumAsByte<Tiers> StartingResourceTier = Tier1);

	UFUNCTION()
		ACharacter* Spawn();

	UPROPERTY()
		bool AutoSpawning = false;

	UFUNCTION()
		void AutoRespawn();

	UFUNCTION()
		void ReduceCurrentSpawnCount(int Amount);

	UFUNCTION()
		void Respawn();

	UFUNCTION()
		void KillAll();

};
