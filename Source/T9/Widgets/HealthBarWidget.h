// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetHealthPercent(float CurrentHealth, float MaxHealth);

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* Health_Bar = nullptr;
};
