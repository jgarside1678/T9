// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T9/Actors/Components/InventoryComponent.h"
#include "Select_Slot.generated.h"

/**
 *
 */
UCLASS()
class T9_API USelect_Slot : public UUserWidget
{
	GENERATED_BODY()
public:

	USelect_Slot(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class AGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventory* Inventory;

	UFUNCTION(BlueprintCallable)
		void InitSlot(struct FSlot NewSlot);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		struct FSlot ItemSlot;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;
};