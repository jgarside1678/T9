// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/CharacterActor.h"
#include "UObject/NoExportTypes.h"
#include "AI/Navigation/NavigationAvoidanceTypes.h"
#include "AllianceCharacter.generated.h"



UCLASS()
class T9_API AAllianceCharacter : public ACharacterActor
{
	GENERATED_BODY()
public:

	// Sets default values for this character's properties
	AAllianceCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
        FVector CommandLocation;

    UPROPERTY(EditAnywhere)
        class AActor* CommandEnemyTarget;

    UPROPERTY(EditAnywhere)
        class AActor* CommandAllianceTarget;

    UPROPERTY(EditAnywhere)
        class AActor* CommandBuildingTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UCrowdFollowingComponent* CrowdManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
        class AResourceActor* CommandedResourceActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
        class AResourceCharacter* CommandedResourceCharacter;

    virtual void SpawnInit(AActor* BuildingSpawn, int SpawnLevel = 1, bool Invuln = false) override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Command", meta = (UnsafeDuringActorConstruction = "true"))
        virtual void Command(FHitResult Hit);

    UFUNCTION(BlueprintCallable, Category = "Command", meta = (UnsafeDuringActorConstruction = "true"))
        FVector GetCommandLocation();

    //virtual void Attack(AActor* Target) override;
};

