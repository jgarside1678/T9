// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/Actors/Items/ItemActor.h"
#include "CharacterActor.generated.h"

USTRUCT(BlueprintType)
struct T9_API FCharacterLevels {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "CharacterLevelStats")
		float BaseDamage = 5;

	UPROPERTY(VisibleAnywhere, Category = "CharacterLevelStats")
		float AttackSpeed = 10;

	UPROPERTY(VisibleAnywhere, Category = "CharacterLevelStats")
		float AttackRange = 0;

	UPROPERTY(VisibleAnywhere, Category = "CharacterLevelStats")
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "CharacterLevelStats")
		float Armour = 0;

	UPROPERTY(VisibleAnywhere, Category = "CharacterLevelStats")
		float KillXP = 0;

	UPROPERTY(VisibleAnywhere, Category = "CharacterLevelStats")
		float KillGold = 0;
};

USTRUCT()
struct T9_API FCharacterEquipment {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		AItemActor* MainHand = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		class UStaticMesh* DefaultMainHand = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		FTransform DefaultMainHandTransformEquiped;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		FTransform DefaultMainHandTransformSheathed;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		AItemActor* OffHand = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		class UStaticMesh* DefaultOffHand = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		FTransform DefaultOffHandTransform;
};



UCLASS()
class T9_API ACharacterActor : public ACharacter, public IDamageInterface, public ISelectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterActor();

private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		class AAI_Controller* Cont;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		int Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		float Damage;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		float Armour;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		float ArmourDamageTakenMultiplier = 1;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		float AttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		float AttackInterval = 2;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics")
		float AttackRange = 5;

	UPROPERTY()
		float HealthBarHeight = 140.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeathTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		bool Invulnerable = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		bool NeedsController = true;

	FTimerHandle DeathTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		TMap<int32, FCharacterLevels> Levels;

	UPROPERTY(VisibleAnywhere, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		FCharacterEquipment Equipment;

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
		class AActor* SpawnBuilding = nullptr;

	UPROPERTY()
		class UWidgetComponent* WidgetComponent;

	UPROPERTY()
		TSubclassOf<UUserWidget> WidgetClass = nullptr;

	UPROPERTY()
		class UHealthBarWidget* HealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;

	//Character Items

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Items", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* MainHandItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Items", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* OffHandItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FItemModifiers ItemModifiers;



	//Combat

	UPROPERTY()
		TSubclassOf<class AProjectile> Projectile = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<DamageType> TypeOfDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		int AttackStreak = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		int AttackStreakForSpecial = 4;

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		virtual void BaseCalculate();

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
	    virtual void CalculateDamage(int BaseAdditionalDamage = 0, float AdditionalDamageMultiplier = 1);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		virtual void CalculateMaxHealth(int BaseAdditionalHealth = 0, float AdditionalHealthMultiplier = 1);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		virtual void CalculateArmour(int BaseAdditionalArmour = 0, float AdditionalArmourMultiplier = 1);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		virtual void CalculateAttackSpeed(int BaseAdditionalAttackSpeed = 0, float AdditionalAttackSpeedMultiplier = 1);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		virtual void CalculateAttackRange(int BaseAdditionalAttackRange = 0, float AdditionalAttackRangeMultiplier = 1);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
	    virtual void DeathInit();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Category = "Character Combat")
		virtual void Attack();

	UFUNCTION(Category = "Character Combat")
		virtual void SpecialAttack();

	UFUNCTION(Category = "Character Combat")
		virtual void ChangePhase(int NewPhase = -1);

	UFUNCTION(Category = "Character Combat")
		virtual void SetTarget(AActor* NewTarget);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* Target;

	class IDamageInterface* TargetInterface;

	UPROPERTY()
		class UAnimMontage* AttackMontage;

	UPROPERTY()
		class UAnimMontage* SpecialAttackMontage;


	UPROPERTY()
		bool TargetBuildings = false;

	UPROPERTY()
		bool TargetCharacters = true;


	UFUNCTION()
		virtual void SpawnInit(AActor* BuildingSpawn, int SpawnLevel = 1, bool Invuln = false, bool SpawnController = true);

	UFUNCTION()
		class AActor* GetSpawnBuilding();

	UPROPERTY(VisibleAnywhere, Category = "Spawn")
		FVector InitalLocation;

	//0 is global
	UPROPERTY()
		float AwarenessDistance = 0;

	UPROPERTY()
		float CapsuleRadius;

	UPROPERTY()
		float CapsuleHeight;

	UFUNCTION()
		void SetLevel(int NewLevel);

	UFUNCTION()
		float GetCurrentHealth();

	UFUNCTION()
		void SetCurrentHealth(float Number);

	UFUNCTION()
		void Heal(float Number);

	UFUNCTION()
		float GetMaxHealth();

	UFUNCTION()
		void SetMaxHealth(float Number);

	UFUNCTION()
		void ResetHealth();

	UFUNCTION()
		float GetDamage();

	UFUNCTION()
		float GetArmour();

	UFUNCTION()
		virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage);

	UFUNCTION()
	    virtual DamageType GetDamageType();

	UFUNCTION()
		virtual bool IsDamageable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDead = false;

	UFUNCTION()
		float GetAttackRange();

	UFUNCTION()
		float GetAttackSpeed();

	UFUNCTION()
		float GetAttackInterval();

	UFUNCTION(BlueprintCallable)
		virtual bool CheckIfDead();

	UFUNCTION()
		virtual void SheathMainHand();

	UFUNCTION()
		virtual void EquipMainHand();

	UFUNCTION()
		virtual void AddMainHand(class AItemActor* NewMainHand = nullptr);

	UFUNCTION()
		virtual void ResetEquipment();

	UFUNCTION()
		bool CheckInvulnerable();

	UFUNCTION()
		void ToggleInvulnerable(bool Input);

	//UI Functions ---------------------------------

	UFUNCTION(BlueprintCallable)
		FCharacterLevels GetCurrentBaseStats();

	UFUNCTION(BlueprintCallable)
		FCharacterLevels GetUpgradeBaseStats();

	//Select Interface Functions ---------------------------------

	UFUNCTION()
		virtual void SetSelected();

	UFUNCTION()
		virtual void SetUnSelected();

};
