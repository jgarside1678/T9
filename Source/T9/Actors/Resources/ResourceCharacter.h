// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "T9/Interfaces/SelectInterface.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/Characters/CharacterActor.h"
#include "ResourceCharacter.generated.h"

UCLASS()
class T9_API AResourceCharacter : public ACharacterActor
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
		float DecayDuration = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basics", Meta = (AllowPrivateAccess = "true"))
	    TArray<class UMaterialInstance*> Materials;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void Init(AResourceActor* OwningResource, FVector SpawnLocation);

	UFUNCTION(BlueprintCallable)
		AResourceActor* GetParentResource();

		virtual void SetSelected() override;

		virtual void SetUnSelected() override;

		virtual void TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeOfDamage = All) override;

		virtual void Attack() override;

		virtual void DeathInit() override;


};
