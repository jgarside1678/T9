// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Alliance_ResourceGatherer.h"
#include "Alliance_Lumberjack.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AAlliance_Lumberjack : public AAlliance_ResourceGatherer
{
	GENERATED_BODY()
public:
	AAlliance_Lumberjack();

protected:
	virtual void BeginPlay() override;

	virtual void SheathMainHand();

	virtual void EquipMainHand();
};
