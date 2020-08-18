// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickUpWidget.h"
#include "T9/MainPlayerState.h"
#include "T9/MainPlayerController.h"
#include "InventoryComponent.h"
#include "T9/Actors/Items/ItemActor.h"
#include "GameHUD.h"


void UItemPickUpWidget::PickUpItem() {
	if (PS && Item) {
		PS->GetInventory()->AddItemToInventory(Item);
	}
}

void UItemPickUpWidget::SellItemForGold()
{
	if (PS && Item) {
		PS->AddGold(Item->GetItemGoldValue());
		Item->Destroy();
	}
}

void UItemPickUpWidget::ShowItemInfo()
{
}

FString UItemPickUpWidget::GetItemName() {
	if (Item) {
		return Item->GetItemName();
	}
	return FString("");
}

void UItemPickUpWidget::NativeConstruct() {
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	if (auto H = PC->GetHUD()) HUD = Cast<AGameHUD>(H);
}

void UItemPickUpWidget::ItemMenuInit(AItemActor* MenuItem) {
	Item = MenuItem;

}