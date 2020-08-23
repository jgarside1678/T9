// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T9/Actors/Components/InventoryComponent.h"
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


	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
		void InitializeInventory();

	UFUNCTION(BlueprintCallable)
		void NativeItemSelected(class UInventorySlot* ItemWidget);

	UFUNCTION(BlueprintCallable)
		UInventoryComponent* GetComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Selection")
		class UInventorySlot* SelectedWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Selection")
		struct FSlot SelectedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
		TSubclassOf<UUserWidget> SlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMainPlayerState* PS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UInventorySelect* InventorySelect;

	//Filter Buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UTexture2D* FilterImageOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UTexture2D* FilterImageOff;

	UPROPERTY(meta = (BindWidget))
		class UWrapBox* InventoryBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowItemsInit")
		TArray<FSlot> Slots;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;

};
