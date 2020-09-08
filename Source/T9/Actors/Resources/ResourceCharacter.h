// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ResourceCharacter.generated.h"

UCLASS()
class T9_API AResourceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AResourceCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
		float MaxResourceAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
		float CurrentResourceAmount;

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
		bool CheckIfDead();

	UFUNCTION(BlueprintCallable)
		AResourceActor* GetParentResource();
};
