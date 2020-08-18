// Fill out your copyright notice in the Description page of Project Settings.


#include "Select_Slot.h"
#include "Inventory.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySelect.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"


USelect_Slot::USelect_Slot(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
}

void USelect_Slot::NativeConstruct()
{
	Super::NativeConstruct();
}

void USelect_Slot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	HUD = Cast<AGameHUD>(PC->GetHUD());
	bIsFocusable = false;

	TArray<UUserWidget*> InventoryWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), InventoryWidgets, UInventory::StaticClass());
	if (InventoryWidgets.Num() > 0) Inventory = Cast<UInventory>(InventoryWidgets[0]);

}

void USelect_Slot::InitSlot(FSlot NewSlot)
{
	ItemSlot = NewSlot;
	if (ItemSlot.Item) {
		ItemImage->SetVisibility(ESlateVisibility::Visible);
		ItemImage->SetBrushFromTexture(ItemSlot.Item->GetItemImage());
	}
	else {
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
		ItemImage->SetBrushFromTexture(nullptr);
	}
}
