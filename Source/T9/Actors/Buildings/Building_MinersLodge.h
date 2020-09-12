// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "Building_MinersLodge.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ABuilding_MinersLodge : public ABuildingActor
{
	GENERATED_BODY()
public:

	ABuilding_MinersLodge(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBuildingSpawnComponent* SpawnComponent;
};
