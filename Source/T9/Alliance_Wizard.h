// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllianceCharacter.h"
#include "Alliance_Wizard.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AAlliance_Wizard : public AAllianceCharacter
{
	GENERATED_BODY()
public:
	AAlliance_Wizard();

protected:
	virtual void BeginPlay() override;
};
