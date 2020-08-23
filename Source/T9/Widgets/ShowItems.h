// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowItems.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UShowItems : public UUserWidget
{
	GENERATED_BODY()
public:

	UShowItems(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	    void AddItems(class UInventorySlot* ClickedSlot);

protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowItemsInit")
		class UInventorySlot* SelectedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowItemsInit")
	    TArray<struct FSlot> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
		class AGameHUD* GameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
		class AMainPlayerState* PS;

	UPROPERTY(meta = (BindWidget))
		class UWrapBox* ItemsBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
		TSubclassOf<UUserWidget> SlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowItemsInit")
		class UInventoryComponent* PlayerInventory;
};
