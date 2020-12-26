// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefensiveBuildingActor.h"
#include "Building_Wizards_Tower.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ABuilding_Wizards_Tower : public ADefensiveBuildingActor
{
	GENERATED_BODY()

public:

	ABuilding_Wizards_Tower(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void Upgrade() override;


	UPROPERTY()
		TArray<class UMaterialInstance*> HairColours1;

	UPROPERTY()
		TArray<class UMaterialInstance*> HairColours2;

};
