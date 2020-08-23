// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Inventory.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySelect.h"
#include "Components/WidgetComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"


UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
	CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	HUD = Cast<AGameHUD>(PC->GetHUD());
	bIsFocusable = false;

	TArray<UUserWidget*> InventoryWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), InventoryWidgets, UInventory::StaticClass());
	if (InventoryWidgets.Num() > 0) Inventory = Cast<UInventory>(InventoryWidgets[0]);

}

void UInventorySlot::InventorySlotInit(struct FSlot InitSlot, class UInventoryComponent* CurrentComponent, class UInventoryComponent* TargetComponent)
{
	ItemSlot = InitSlot;
	CurrentInventoryComponent = CurrentComponent;
	TargetInventoryComponent = TargetComponent;
	if (ItemSlot.Item) {
		ItemImage->SetVisibility(ESlateVisibility::Visible);
		ItemImage->SetBrushFromTexture(ItemSlot.Item->GetItemImage());
	}
	else ItemImage->SetVisibility(ESlateVisibility::Hidden);

}

void UInventorySlot::Interact()
{
	if (CurrentInventoryComponent && TargetInventoryComponent) {
		AItemActor* ReplacedItem;
		if (TargetInventoryComponent->AddItemToInventorySlot(HUD->SelectedSlot->ItemSlot, ItemSlot.Item, ReplacedItem)) {
			int Index;
			CurrentInventoryComponent->CheckForItemInInventory(ItemSlot.Item, Index);
			CurrentInventoryComponent->RemoveItemFromInventory(Index);
			if(ReplacedItem) CurrentInventoryComponent->AddItemToInventory(ReplacedItem);
		}
		if (HUD->ShowItemsState) HUD->HideShowItems();
	}
	else if (CurrentInventoryComponent == PS->GetInventory()) {
		HUD->GetInventoryWidget()->NativeItemSelected(this);
	}
	else {
		HUD->ShowItemsForSlot(this);
	}
}

UInventoryComponent* UInventorySlot::GetCurrentComponent()
{
	return CurrentInventoryComponent;
}

UInventoryComponent* UInventorySlot::GetTargetComponent()
{
	return TargetInventoryComponent;
}

FSlot UInventorySlot::GetItemSlot()
{
	return ItemSlot;
}
