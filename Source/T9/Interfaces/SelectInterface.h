// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class USelectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class T9_API ISelectInterface
{
	GENERATED_BODY()


public:

	UFUNCTION()
		virtual void SetSelected();

	UFUNCTION()
		virtual void SetUnSelected();

	UFUNCTION(BlueprintCallable)
		virtual float GetDamage();

	UFUNCTION(BlueprintCallable)
		virtual float GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
		virtual float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
		virtual FString GetName();

	UFUNCTION(BlueprintCallable)
		virtual int GetLevel();

};
