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
	static ConstructorHelpers::FObjectFinder<UTexture2D> AnyTypeImage(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_plus.btn_icon_plus'"));
	TypeImages.Add(AnyType, AnyTypeImage.Object);
	static ConstructorHelpers::FObjectFinder<UTexture2D> ToolTypeImage(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_hammer.btn_icon_hammer'"));
	TypeImages.Add(Tool, ToolTypeImage.Object);
	static ConstructorHelpers::FObjectFinder<UTexture2D> WeaponTypeImage(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_sword.btn_icon_sword'"));
	TypeImages.Add(Weapon, WeaponTypeImage.Object);
	static ConstructorHelpers::FObjectFinder<UTexture2D> ArmourTypeImage(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_helmet.btn_icon_helmet'"));
	TypeImages.Add(Armour, ArmourTypeImage.Object);
	static ConstructorHelpers::FObjectFinder<UTexture2D> ArtefactTypeImage(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_sparkle.btn_icon_sparkle'"));
	TypeImages.Add(Artefact, ArtefactTypeImage.Object);
	static ConstructorHelpers::FObjectFinder<UTexture2D> OtherTypeImage(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_compass.btn_icon_compass'"));
	TypeImages.Add(Other, OtherTypeImage.Object);
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
		TypeImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
		TypeImage->SetVisibility(ESlateVisibility::Visible);
		TypeImage->SetBrushFromTexture(TypeImages[ItemSlot.SlotType]);
	}
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
