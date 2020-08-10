// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
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

	virtual void NativeOnInitialized() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class AGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventory* Inventory;

	//UFUNCTION(BlueprintCallable)
	//	void InventorySlotPressed(FSlot ItemSlot);

};
