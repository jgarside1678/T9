// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:

	UInventorySlot(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AMainPlayerController* PC;
};
