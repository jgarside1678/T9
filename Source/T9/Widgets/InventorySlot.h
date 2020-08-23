// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T9/Actors/Components/InventoryComponent.h"
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


	UFUNCTION(BlueprintCallable)
		void InventorySlotInit(struct FSlot InitSlot, class UInventoryComponent* CurrentComponent, class UInventoryComponent* TargetComponent = nullptr);

	UFUNCTION(BlueprintCallable)
		void Interact();

	UFUNCTION()
		class UInventoryComponent* GetCurrentComponent();

	UFUNCTION()
		class UInventoryComponent* GetTargetComponent();

	UFUNCTION()
		struct FSlot GetItemSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UCanvasPanelSlot* CanvasSlot;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		struct FSlot ItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventoryComponent* CurrentInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventoryComponent* TargetInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class AGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class AMainPlayerState* PS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventory* Inventory;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;
};
