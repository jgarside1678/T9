// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/Actors/Items/ItemActor.h"
#include "T9/Interfaces/SelectInterface.h"
#include "BuildingActor.generated.h"



USTRUCT(BlueprintType)
struct FBuildingCosts {

	GENERATED_BODY()

		FBuildingCosts& operator+=(const FBuildingCosts& rhs) {
		Gold += rhs.Gold;
		Wood += rhs.Wood;		
		Stone += rhs.Stone;
		Food += rhs.Food;
		return *this;
	}

	FBuildingCosts& operator*(float rhs) {
		Gold *= rhs;
		Wood *= rhs;
		Stone *= rhs;
		Food *= rhs;
		return *this;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Wood = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Stone = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Food = 0;

	inline FBuildingCosts& operator-=(const FBuildingCosts& Right) {
		this->Gold -= Right.Gold;
		this->Wood -= Right.Wood;
		this->Stone -= Right.Stone;
		this->Food -= Right.Food;
		return *this;
	}
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

	inline FBuildingProduction& operator-=(const FBuildingProduction& Right) {
		this->Gold -= Right.Gold;
		this->Wood -= Right.Wood;
		this->Stone -= Right.Stone;
		this->Food -= Right.Food;
		return *this;
	}
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

	inline FBuildingAttack& operator-=(const FBuildingAttack& Right) {
		this->Damage -= Right.Damage;
		this->AttackSpeed -= Right.AttackSpeed;
		this->AttackRangeMultipler -= Right.AttackRangeMultipler;
		return *this;
	}
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
		float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Image = nullptr;

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

	inline FBuildingUpgrades& operator-=(const FBuildingUpgrades& Right) {
		this->XP -= Right.XP;
		this->PowerRating -= Right.PowerRating;
		this->MaxHealth -= Right.MaxHealth;
		this->Defence -= Right.Defence;
		this->Cost -= Right.Cost;
		this->Attack -= Right.Attack;
		this->Production -= Right.Production;
		return *this;
	}
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float Defence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float DefenceDamageTakenMultiplier = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float AttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float AttackInterval = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<DamageType> TypeOfDamage = Alliance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		FString BuildingName = "Building";

	UPROPERTY(VisibleAnywhere, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		TMap<int32, FBuildingUpgrades> Upgrades;

	UPROPERTY(VisibleAnywhere, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		FBuildingCosts TotalCosts;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		class AGameGridActor* Grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class USceneComponent* MeshDisplacement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BuildingRangeCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;

	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		int BuildingDetectionRange = 3;

	UPROPERTY()
		int OutlineColour = 0;

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		class UAudioComponent* UpgradeAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		bool Disabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		bool RecentlyRendered = true;

	//Building Inventory and Items

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Inventory")
		class  UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FItemModifiers ItemModifiers;

	//Building Widgets

	UPROPERTY()
		float HealthBarHeight = 500.0f;

	UPROPERTY()
		class UWidgetComponent* HealthWidgetComponent;

	UPROPERTY()
		TSubclassOf<UUserWidget> HealthWidgetClass = nullptr;

	UPROPERTY()
		class UHealthBarWidget* HealthBar;

	UPROPERTY()
		float QuickSelectWidgetHeight = 100.0f;

	UPROPERTY()
		class UWidgetComponent* QuickSelectWidgetComponent;

	UPROPERTY()
		TSubclassOf<UUserWidget> QuickSelectWidgetClass = nullptr;

	UPROPERTY()
		class UQuickSelectMenu* QuickSelectMenu;

	TArray<UActorComponent*> InstancedStaticMeshArray;


public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		FVector BuildingExtent;

	UFUNCTION(Category = "Building Basics")
		int GetBuildingCount();

	UFUNCTION(Category = "Building Basics")
		int GetMaxBuildingCount();

	UFUNCTION(BlueprintCallable)
		virtual void Upgrade();

	//For initalising spawn arguments
	UFUNCTION()
		virtual void BuildingInit(AGameGridActor* BuildingGrid, FVector PivotLocation, FVector CornerLocation, int Rotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		int GridRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Basics")
		bool Upgrading = false;

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
		virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage = All);

	UFUNCTION()
		virtual void DamageEnemy(AActor* Actor, float AmountOfDamage);

	UFUNCTION()
		virtual DamageType GetDamageType();

	UFUNCTION()
		virtual bool IsDamageable();

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

	UFUNCTION(BlueprintCallable)
		class AActor* GetTarget();

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

	UFUNCTION(BlueprintCallable)
		float GetDefence();

	UFUNCTION(BlueprintCallable)
		float GetAttackRange();

	UFUNCTION(BlueprintCallable)
		float GetAttackSpeed();

	UFUNCTION(BlueprintCallable)
		class UTexture2D* GetImage();

	UPROPERTY()
		bool IsDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GridSpace;

	//Disable Building

	UFUNCTION(BlueprintCallable)
		void RestoreBuilding();

	UFUNCTION()
		void ToggleDisabled();

	UFUNCTION()
		void SetDisabled(bool Input);

	UFUNCTION()
		bool GetDisabled();

	UFUNCTION()
		void CalculateDamage();

	UFUNCTION()
		void CalculateAttackRange();

	UFUNCTION()
		virtual void CalculateAttackSpeed();

	UFUNCTION()
		void CalculateMaxHealth();

	UFUNCTION()
		void CalculateDefence();


	//Functions used for Menus

	UFUNCTION(BlueprintCallable)
		FBuildingUpgrades GetCurrentBaseStats();

	UFUNCTION(BlueprintCallable)
		FBuildingUpgrades GetUpgradeBaseStats();

	//Inventory Functions

	UFUNCTION(BlueprintCallable)
		class UInventoryComponent* GetInventory();

	UFUNCTION(BlueprintCallable)
		void UpdateBuildingModifiers();

	UFUNCTION(BlueprintCallable)
		class UWidgetComponent* GetHealthWidget();

	UFUNCTION(BlueprintCallable)
		class UWidgetComponent* GetQuickSelectWidget();

};

