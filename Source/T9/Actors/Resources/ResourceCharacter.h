// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "T9/Interfaces/SelectInterface.h"
#include "T9/Interfaces/DamageInterface.h"
#include "ResourceCharacter.generated.h"

UCLASS()
class T9_API AResourceCharacter : public ACharacter, public ISelectInterface, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AResourceCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DeathTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		AResourceActor* ParentResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		FVector InitialLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		bool Dead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		ACharacter* CombatTarget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		float DecayDuration = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
	    TArray<class UMaterialInstance*> Materials;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
	     class UAnimMontage* IdleMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void Init(AResourceActor* OwningResource, FVector SpawnLocation);

	UFUNCTION(BlueprintCallable)
		AResourceActor* GetParentResource();

	UFUNCTION()
		virtual void SetSelected();

	UFUNCTION()
		virtual void SetUnSelected();

	UPROPERTY()
		float CapsuleRadius = 50;

	UFUNCTION()
		virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeOfDamage = All);


	UFUNCTION()
		virtual void DamageEnemy(AActor* Actor, float AmountOfDamage);


	UFUNCTION(BlueprintCallable)
		virtual bool CheckIfDead();

	UFUNCTION()
		void DeathInit();


};
