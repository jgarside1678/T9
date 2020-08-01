// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageInterface.h"
#include "CharacterActor.generated.h"

USTRUCT()
struct T9_API FCharacterLevels {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Attack")
		float BaseDamage = 5;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
		float AttackRange = 0;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "XP")
		float KillXP = 0;

	UPROPERTY(VisibleAnywhere, Category = "XP")
		float KillGold = 0;
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

	UPROPERTY(VisibleAnywhere, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		TMap<int32, FCharacterLevels> Levels;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* MainHandItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Leveling")
		int Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
		float Damage;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CurrentHealth;

	UPROPERTY()
		float HealthBarHeight = 140.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeathTime = 1.0f;

	FTimerHandle DeathTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
	    UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
	    bool Invulnerable = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Basics", Meta = (AllowPrivateAccess = "true"))
		bool NeedsController = true;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		bool TargetBuildings = false;

	UPROPERTY()
		bool TargetCharacters = true;

	UPROPERTY()
		class UAnimMontage* AttackMontage;

	UPROPERTY()
		class UAnimMontage* CurrentMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* CurrentTarget;

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

	UFUNCTION()
		void SetLevel(int NewLevel);

	UFUNCTION()
		float GetCurrentHealth();

	UFUNCTION()
		void SetCurrentHealth(float Number);

	UFUNCTION()
		float GetMaxHealth();

	UFUNCTION()
		void SetMaxHealth(float Number);

	UFUNCTION()
		void ResetHealth();

	UFUNCTION()
		float GetDamage();

	UFUNCTION()
		virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage);

	UFUNCTION()
		virtual void DamageEnemy(AActor* Actor, float AmountOfDamage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDead = false;

	UFUNCTION()
		float GetAttackRange();

	UPROPERTY()
		int AttackStreak = 0;

	UFUNCTION()
		virtual void Attack(AActor* Target, int Number = 1);

	UFUNCTION()
		virtual void SpecialAttack(AActor* Target, int Number);

	UFUNCTION()
		virtual bool CheckIfDead();

	UFUNCTION()
		virtual void SheathMainHand();

	UFUNCTION()
		virtual void EquipMainHand();

	UFUNCTION()
		bool CheckInvulnerable();

	UFUNCTION()
		void ToggleInvulnerable(bool Input);

	//UFUNCTION()
	//	float GetDamage();

};
