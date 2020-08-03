// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPickUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UItemPickUpWidget : public UUserWidget
{
	GENERATED_BODY()
public: 

	UFUNCTION(BlueprintCallable)
		void ItemMenuInit(class AItemActor* MenuItem);

	UFUNCTION(BlueprintCallable)
	    void PickUpItem();

	UFUNCTION(BlueprintCallable)
		void SellItemForGold();

	UFUNCTION(BlueprintCallable)
		void ShowItemInfo();

private:

	UPROPERTY()
		class AItemActor* Item;

	virtual void NativeConstruct() override;

	UPROPERTY()
		class AMainPlayerController* PC;

	UPROPERTY()
		class AMainPlayerState* PS;

	UPROPERTY()
		class AGameHUD* HUD;
};
