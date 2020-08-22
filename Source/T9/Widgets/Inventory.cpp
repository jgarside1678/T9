// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySelect.h"
#include "Components/WrapBox.h"
#include "InventorySlot.h"
#include "T9/MainPlayerState.h"


UInventory::UInventory(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlot(TEXT("WidgetBlueprint'/Game/UI/InventorySlot_BP.InventorySlot_BP_C'"));
	if (ItemSlot.Succeeded()) {
		SlotClass = ItemSlot.Class;
	}
}

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();
}


void UInventory::NativePreConstruct() {
	if (!PC) 	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	if (PC) {
		HUD = Cast<AGameHUD>(PC->GetHUD());
		PS = Cast<AMainPlayerState>(PC->PlayerState);
		if (PS) InventoryComponent = PS->GetInventory();
	}
	Super::NativePreConstruct();
}

void UInventory::InitializeInventory()
{
	Slots = InventoryComponent->GetItems();
	InventoryBox->ClearChildren();
	for (int x = 0; x < Slots.Num(); x++) {
		UInventorySlot* NewSlot = (UInventorySlot*)CreateWidget(this, SlotClass);
		NewSlot->InventorySlotInit(Slots[x], InventoryComponent);
		InventoryBox->AddChildToWrapBox(NewSlot);
	}
}

UInventoryComponent* UInventory::GetComponent()
{
	return InventoryComponent;
}

void UInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}