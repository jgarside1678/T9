// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingActor.h"
#include "ResourceBuildingActor.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AResourceBuildingActor : public ABuildingActor
{
	GENERATED_BODY()
public :
	AResourceBuildingActor();

protected:

	virtual void BeginPlay() override;

	FTimerHandle PrimaryResourceTimerHandle;

	UPROPERTY()
		bool Gathering = false;

	UFUNCTION()
		virtual void ResourceInit();

	UPROPERTY()
		float ResourceTick = 5.0f;

	UFUNCTION()
		void GatherResources(int Gold, int Wood = 0, int Stone = 0, int Food = 0);

	UFUNCTION()
		void BuildingGatherResources(FBuildingProduction Production);

	UFUNCTION()
		void GatherGold(int Gold);

	UFUNCTION()
		void GatherWood(int Wood);

	UFUNCTION()
		void GatherStone(int Stone);

	UFUNCTION()
		void GatherFood(int Food);

};
