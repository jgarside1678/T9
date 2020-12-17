// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/AI/AI_Controller.h"
#include "Basic_Enemy_Controller.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ABasic_Enemy_Controller : public AAI_Controller
{
	GENERATED_BODY()
public:
	ABasic_Enemy_Controller(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	void BeginPlay() override;

	void OnPossess(APawn* const pawn) override;

};
