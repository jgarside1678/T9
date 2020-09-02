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
		UStaticMesh* DefaultMainHand = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		AItemActor* OffHand = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
		UStaticMesh* DefaultOffHand = nullptr;
};



UCLASS()
class T9_API ACharacterActor : public ACharacter, public IDamageInterface
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
	    virtual void CalculateDamage(int BaseAdditionalDamage = 0);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		virtual void CalculateMaxHealth(int BaseAdditionalHealth = 0);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
		virtual void CalculateArmour(int BaseAdditionalHealth = 0);

	UFUNCTION(Category = "Character Combat", Meta = (AllowPrivateAccess = "true"))
	    virtual void DeathInit();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Category = "Character Combat")
		virtual void Attack(AActor* Target);

	UFUNCTION(Category = "Character Combat")
		virtual void SpecialAttack(AActor* Target);

	UFUNCTION(Category = "Character Combat")
		virtual void ChangePhase(int NewPhase = -1);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* CurrentTarget;

	UPROPERTY()
		class UAnimMontage* AttackMontage;

	UPROPERTY()
		class UAnimMontage* SpecialAttackMontage;


	UPROPERTY()
		bool TargetBuildings = false;

	UPROPERTY()
		bool TargetCharacters = true;


	UFUNCTION()
		void SpawnInit(AActor* BuildingSpawn, int SpawnLevel = 1, bool Invuln = false, bool SpawnController = true);

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
		virtual void DamageEnemy(AActor* Actor, float AmountOfDamage);

	UFUNCTION()
	    virtual DamageType GetDamageType();

	UFUNCTION()
		virtual bool IsDamageable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDead = false;

	UFUNCTION()
		float GetAttackRange();


	UFUNCTION()
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


	UFUNCTION(BlueprintCallable)
		FCharacterLevels GetCurrentBaseStats();

	UFUNCTION(BlueprintCallable)
		FCharacterLevels GetUpgradeBaseStats();

};
