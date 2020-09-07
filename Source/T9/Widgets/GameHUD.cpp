// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "T9/T9GameModeBase.h"
#include "T9/MainPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "T9/Interfaces/SelectInterface.h"
#include "HUDWidget.h"
#include "SelectMenuWidget.h"
#include "BuildMenu.h"
#include "InventorySlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/StaticMeshComponent.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "T9/Actors/Resources/ResourceActor.h"
//#include "Blueprint/WidgetLayoutLibrary.h"
#include "LevelUp.h"
#include "ShowItems.h"
#include "PlayerAlert.h"
#include "QuickSelectMenu.h"
#include "T9/Actors/GameGridActor.h"
#include "T9/Actors/Items/ItemActor.h"
#include "Inventory.h"


AGameHUD::AGameHUD() {



	static ConstructorHelpers::FClassFinder<UUserWidget> Build(TEXT("WidgetBlueprint'/Game/UI/BuildMenu_BP1.BuildMenu_BP1_C'"));
	if (Build.Succeeded()) BuildMenuWidget = CreateWidget<UBuildMenu>(GetWorld(), Build.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> MainHUD(TEXT("WidgetBlueprint'/Game/UI/HUDMenu.HUDMenu_C'"));
	if(MainHUD.Succeeded())	HUDMenuWidget = CreateWidget<UHUDWidget>(GetWorld(), MainHUD.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> Select(TEXT("WidgetBlueprint'/Game/UI/SelectMenu.SelectMenu_C'"));
	if (Select.Succeeded()) SelectMenuWidget = CreateWidget<USelectMenuWidget>(GetWorld(), Select.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> QuickSelect(TEXT("WidgetBlueprint'/Game/UI/QuickSelectMenu_BP.QuickSelectMenu_BP_C'"));
	if (QuickSelect.Succeeded()) QuickSelectMenu = CreateWidget<UQuickSelectMenu>(GetWorld(), QuickSelect.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> Inventory(TEXT("WidgetBlueprint'/Game/UI/Inventory_BP.Inventory_BP_C'"));
	if (Inventory.Succeeded()) InventoryWidget = CreateWidget<UInventory>(GetWorld(), Inventory.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> LevelUp(TEXT("WidgetBlueprint'/Game/UI/LevelUp_BP.LevelUp_BP_C'"));
	if (LevelUp.Succeeded()) LevelUpWidget = CreateWidget<ULevelUp>(GetWorld(), LevelUp.Class);


	static ConstructorHelpers::FClassFinder<UUserWidget> Alert(TEXT("WidgetBlueprint'/Game/UI/PlayerAlert_BP.PlayerAlert_BP_C'"));
	if (Alert.Succeeded()) PlayerMessage = CreateWidget<UPlayerAlert>(GetWorld(), Alert.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> FilterItems(TEXT("WidgetBlueprint'/Game/UI/ShowItems_BP.ShowItems_BP_C'"));
	if (FilterItems.Succeeded()) ShowItems = CreateWidget<UShowItems>(GetWorld(), FilterItems.Class);

	UWorld* World = GetWorld();
	if (World) {
		GameMode = (AT9GameModeBase*)UGameplayStatics::GetGameMode(World);
		if (GameMode != nullptr) {
			GameGrid = GameMode->Grid;
		}
	}
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (HUDMenuWidget) {

		HUDMenuWidget->AddToViewport();
	}

}

void AGameHUD::SetSelectedBuildMenuObject(FBuildingMenuSlot Selection) {
	if (SelectedBuildMenuObject.Building != NULL) {
		GameGrid->DestroyPreviewObject();
		PreviewBuilding = nullptr;
	}
	SelectedBuildMenuObject = Selection;
	if (SelectedBuildMenuObject.Building != NULL) {
		PreviewBuilding = GameGrid->CreatePreviewObject(SelectedBuildMenuObject);
		if (ABuildingActor* Building = Cast<ABuildingActor>(PreviewBuilding)) GameGrid->ScaleSelectionTile(Building->GridLength.X, Building->GridLength.Y);
	}
}

void AGameHUD::RotateSelectedBuilding(float RotationAmount)
{
	GameGrid->RotatePreviewObject(RotationAmount);
}

void AGameHUD::ShowBuildMenu()
{
	if(GameGrid) GameGrid->ToggleSelectionTile(true);
	if (BuildMenuWidget) {
		BuildMenuState = true;
		BuildMenuWidget->AddToViewport();
		GameGrid->SetActorHiddenInGame(false);
		GameGrid->ToggleGridSpaces(true);
		//if (PC) {
		//	FInputModeGameAndUI InputMode;
		//	PC->SetInputMode(FInputModeGameOnly());
		//}
	}
}

void AGameHUD::HideSelectMenu()
{
	FHitResult EmptyHit;
	SetGameObjectSelected(EmptyHit);
}

void AGameHUD::ShowSelectMenu()
{
	if (SelectMenuWidget) SelectMenuWidget->AddToViewport();
}

void AGameHUD::ShowInventory()
{
	if (InventoryWidget) {
		InventoryWidget->AddToViewport();
		InventoryState = true;
	}
}

void AGameHUD::HideInventory()
{
	if (InventoryWidget) {
		InventoryWidget->RemoveFromViewport();
		InventoryState = false;
	}
}

void AGameHUD::ShowPlayerMessage()
{
	if (PlayerMessage) {
		PlayerMessage->AddToViewport();
		MessageState = true;
	}
}

void AGameHUD::HidePlayerMessage()
{
	if (PlayerMessage) {
		PlayerMessage->RemoveFromViewport();
		MessageState = false;
	}
}

void AGameHUD::ShowShowItems()
{
	if (ShowItems) {
		ShowItems->AddToViewport();
		ShowItemsState = true;
	}
}

void AGameHUD::HideShowItems()
{
	if (ShowItems) {
		ShowItems->RemoveFromViewport();
		ShowItemsState = false;
	}
}

void AGameHUD::ShowItemsForSlot(class UInventorySlot* ClickedSlot)
{
	ShowItems->SetPositionInViewport(ClickedSlot->GetCachedGeometry().GetAbsolutePosition(), false);
	//ShowItems->SetPositionInViewport(ClickedSlot->CanvasSlot->GetPosition());
	if (ClickedSlot == SelectedSlot && ShowItemsState) HideShowItems();
	else if(!ShowItemsState) ShowShowItems();
	SelectedSlot = ClickedSlot;
	ShowItems->AddItems(SelectedSlot);
}

void AGameHUD::HideBuildMenu()
{
	//Reseting
	GameGrid->ScaleSelectionTile(1, 1);
	GameGrid->DestroyPreviewObject();
	GameGrid->SetActorHiddenInGame(true);
	GameGrid->ToggleGridSpaces(false);
	//GameGrid->ToggleSelectionTile(false);
	PreviewBuilding = nullptr;

	if (BuildMenuWidget) {
		BuildMenuState = false;
		BuildMenuWidget->RemoveFromViewport();
	}
}



void AGameHUD::AddPlayerAlert(FString Title, FString Message, float MessageTimeout)
{
	if(!PlayerMessage->IsInViewport()) ShowPlayerMessage();
	PlayerMessage->SetAlertContent(Title, Message);
	if(MessageTimeout > 0) GetWorldTimerManager().SetTimer(PlayerAlertHandle, this, &AGameHUD::HidePlayerMessage, MessageTimeout, false, MessageTimeout);
}

//Sets actual Objects in game selected
void AGameHUD::SetGameObjectSelected(FHitResult Hit)
{
	if (SelectMenuWidget->IsInViewport()) SelectMenuWidget->RemoveFromViewport();
	if (QuickSelectMenu->IsInViewport()) QuickSelectMenu->RemoveFromViewport();
	if (SelectedObject) {
		if (SelectMenuWidget)SelectMenuWidget->RemoveFromViewport();
		if (AItemActor* Item = Cast<AItemActor>(SelectedObject)) {
			if(Item->WidgetComponent) Item->WidgetComponent->SetVisibility(false);
		}
		if (ISelectInterface* Select = Cast<ISelectInterface>(HitActor)) Select->SetUnSelected();
	}

	HitActor = Hit.Actor.Get();
	if (HitActor)
	{
		float LocationX, LocationY;
		PC->GetMousePosition(LocationX, LocationY);
		SelectedObject = HitActor;
		if (ISelectInterface* Select = Cast<ISelectInterface>(HitActor)) {
			if (!QuickSelectMenu->IsInViewport()) QuickSelectMenu->AddToViewport();
			QuickSelectMenu->SetPositionInViewport(FVector2D(LocationX, LocationY) - FVector2D(120, 30));
			QuickSelectMenu->Init(SelectedObject);
			Select->SetSelected();

		}
		else if (AItemActor* Item = Cast<AItemActor>(SelectedObject)) {
			if (Item->WidgetComponent) {
				Item->WidgetComponent->SetVisibility(true);
			}
		}
		else if (AResourceCharacter* Spawned = Cast<AResourceCharacter>(HitActor)) {
			SelectedObject = Spawned->GetParentResource();
			QuickSelectMenu->SetPositionInViewport(FVector2D(LocationX, LocationY) - FVector2D(120, 30));
			QuickSelectMenu->Init(SelectedObject);
			Spawned->GetParentResource()->SetSelected();
		}
	}
	if (ShowItemsState) HideShowItems();
}


USelectMenuWidget* AGameHUD::GetSelectMenu() {
	return SelectMenuWidget;
}

UInventory* AGameHUD::GetInventoryWidget()
{
	return InventoryWidget;
}

void AGameHUD::ShowLevelUp()
{
	LevelUpWidget->AddToViewport();
}

void AGameHUD::HideLevelUp()
{
	LevelUpWidget->RemoveFromViewport();
}

void AGameHUD::PlayerLevelUp(int Level)
{
	if(LevelUpWidget->IsInViewport()) HideLevelUp();
	GetWorld()->GetTimerManager().ClearTimer(LevelUpTimerHandle);
	LevelUpWidget->LevelUpInit(Level);
	ShowLevelUp();
	GetWorldTimerManager().SetTimer(LevelUpTimerHandle, this, &AGameHUD::HideLevelUp, 5, false, 5);
}

ULevelUp* AGameHUD::GetLevelUpWidget()
{
	return LevelUpWidget;
}

