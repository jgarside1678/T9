// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Alliance/Alliance_ResourceGatherer.h"
#include "Alliance_Hunter.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AAlliance_Hunter : public AAlliance_ResourceGatherer
{
	GENERATED_BODY()
public:
	AAlliance_Hunter();

protected:
	virtual void BeginPlay() override;

	virtual void SheathMainHand() override;

	virtual void EquipMainHand() override;
};
