// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickUpWidget.h"
#include "MainPlayerState.h"
#include "MainPlayerController.h"
#include "ItemActor.h"
#include "GameHUD.h"


void UItemPickUpWidget::PickUpItem() {
	if (PS && Item) {
		PS->AddItemToInventory(Item);
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

void UItemPickUpWidget::NativeConstruct() {
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	if (auto H = PC->GetHUD()) HUD = Cast<AGameHUD>(H);
}

void UItemPickUpWidget::ItemMenuInit(AItemActor* MenuItem) {
	Item = MenuItem;

}