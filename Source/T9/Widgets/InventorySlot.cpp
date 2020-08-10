// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Inventory.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySelect.h"
#include "Components/WidgetComponent.h"


UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	HUD = Cast<AGameHUD>(PC->GetHUD());
	bIsFocusable = false;
	
    TArray<UUserWidget*> InventoryWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), InventoryWidgets, UInventory::StaticClass());
	if (InventoryWidgets.Num() > 0) Inventory = Cast<UInventory>(InventoryWidgets[0]);

}
//
//void UInventorySlot::InventorySlotPressed(FSlot ItemSlot)
//{
//	if(Inventory && Inventory->InventorySelect) {
//		UInventorySelect* Select = Inventory->InventorySelect;
//		if(Select) Select->UpdateSelected(ItemSlot);
//		UE_LOG(LogTemp, Warning, TEXT("pressed"));
//	}
//}