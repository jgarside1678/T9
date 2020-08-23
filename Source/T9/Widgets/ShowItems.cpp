// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowItems.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
#include "InventorySlot.h"
#include "T9/Actors/Components/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "T9/MainPlayerState.h"

UShowItems::UShowItems(const FObjectInitializer& ObjectInit) : Super(ObjectInit)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlot(TEXT("WidgetBlueprint'/Game/UI/InventorySlot_BP.InventorySlot_BP_C'"));
	if (ItemSlot.Succeeded()) {
		SlotClass = ItemSlot.Class;
	}
}

void UShowItems::NativeConstruct()
{

	Super::NativeConstruct();
}


void UShowItems::NativePreConstruct() {
	if (!PC) 	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	if (PC) {
		GameHUD = Cast<AGameHUD>(PC->GetHUD());
		PS = Cast<AMainPlayerState>(PC->PlayerState);
		if (PS) PlayerInventory = PS->GetInventory();
	}
	Super::NativePreConstruct();
}


void UShowItems::AddItems(class UInventorySlot* ClickedSlot)
{
	SelectedSlot = ClickedSlot;
	ItemsBox->ClearChildren();
	Slots = PlayerInventory->GetItems();
	for (int x = 0; x < Slots.Num(); x++) {
		if (Slots[x].Item) {
			FSlot ItemSlot = ClickedSlot->GetItemSlot();
			if (Slots[x].SlotType == ItemSlot.SlotType || ItemSlot.SlotType == AnyType || Slots[x].SlotType == AnyType) {
				if (Slots[x].SlotSubType == ItemSlot.SlotSubType || ItemSlot.SlotSubType == AnyType || Slots[x].SlotSubType == AnyType) {
					UInventorySlot* NewItem = (UInventorySlot*)(CreateWidget(ItemsBox, SlotClass));
					NewItem->InventorySlotInit(Slots[x], PlayerInventory, ClickedSlot->GetCurrentComponent());
					ItemsBox->AddChild(NewItem);
				}
			}
		}
	}
}
