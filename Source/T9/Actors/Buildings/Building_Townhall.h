// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceBuildingActor.h"
#include "Building_Townhall.generated.h"


/**
 * 
 */

UCLASS()
class T9_API ABuilding_Townhall : public AResourceBuildingActor
{
	GENERATED_BODY()
public:

	ABuilding_Townhall(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBuildingSpawnComponent* SpawnComponent;

	//virtual int GetCurrentBuildingCount();

	//virtual int GetMaxBuildingCount();


protected:
	virtual void BeginPlay() override;

	virtual void Upgrade() override;

	virtual void ResourceInit() override;

};
