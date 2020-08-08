// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/AI/AI_Controller.h"
#include "Alliance_Gatherer_Controller.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AAlliance_Gatherer_Controller : public AAI_Controller
{
	GENERATED_BODY()
public:
	AAlliance_Gatherer_Controller(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	void BeginPlay() override;

	void OnPossess(APawn* const pawn) override;

};
