// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventorySelect.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UInventorySelect : public UUserWidget
{
	GENERATED_BODY()
public:
	UInventorySelect(const FObjectInitializer& ObjectInit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		struct FSlot CurrentSlot;

	//UFUNCTION(BlueprintNativeEvent)
	//void UpdateSelected(struct FSlot NewSlot);	
	//void UpdateSelected_Implementation(struct FSlot NewSlot);
};
