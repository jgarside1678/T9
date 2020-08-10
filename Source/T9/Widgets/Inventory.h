// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:

	UInventory(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;


	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AGameHUD* HUDPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventorySelect* InventorySelect;
};
