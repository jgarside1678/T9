// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "T9GameModeBase.h"
#include "MainPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "SelectInterface.h"
#include "HUDWidget.h"
#include "SelectMenuWidget.h"
#include "BuildMenuWidget.h"
#include "GameGridActor.h"
#include "ItemActor.h"
#include "Widgets/Inventory.h"


AGameHUD::AGameHUD() {

	static ConstructorHelpers::FObjectFinder<UDataTable> BuildingsDataTableObject(TEXT("DataTable'/Game/DataTables/Buildings.Buildings'"));
	BuildMenuBuildings = BuildingsDataTableObject.Object;


	static ConstructorHelpers::FClassFinder<UUserWidget> Widget1(TEXT("WidgetBlueprint'/Game/UI/BuildMenu.BuildMenu_C'"));
	if (Widget1.Succeeded()) BuildMenuWidget = CreateWidget<UBuildMenuWidget>(GetWorld(), Widget1.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> Widget2(TEXT("WidgetBlueprint'/Game/UI/HUDMenu.HUDMenu_C'"));
	if(Widget2.Succeeded())	HUDMenuWidget = CreateWidget<UHUDWidget>(GetWorld(), Widget2.Class);

	static ConstructorHelpers::FClassFinder<UUserWidget> Widget3(TEXT("WidgetBlueprint'/Game/UI/SelectMenu.SelectMenu_C'"));
	if (Widget3.Succeeded()) SelectMenuWidget = CreateWidget<USelectMenuWidget>(GetWorld(), Widget3.Class);


	static ConstructorHelpers::FClassFinder<UUserWidget> Inventory(TEXT("WidgetBlueprint'/Game/UI/Inventory_BP.Inventory_BP_C'"));
	if (Inventory.Succeeded()) InventoryWidget = CreateWidget<UInventory>(GetWorld(), Inventory.Class);

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

void AGameHUD::SetSelectedBuildMenuObject(FString Selection) {
	if (BuildMenuBuildings) {
		if (SelectedBuildMenuObject) {
			GameGrid->DestroyPreviewObject();
			PreviewBuilding = nullptr;
		}
		static const FString ContextString(TEXT("Spawn Buildings Context"));
		SelectedBuildMenuObject = BuildMenuBuildings->FindRow<FBuildingMenu>(FName(Selection), ContextString, true);
		if (SelectedBuildMenuObject) {
			PreviewBuilding = GameGrid->CreatePreviewObject(*SelectedBuildMenuObject);
			if (ABuildingActor* Building = Cast<ABuildingActor>(PreviewBuilding)) GameGrid->ScaleSelectionTile(Building->GridLength.X, Building->GridLength.Y);
		}

	}
}

void AGameHUD::RotateSelectedBuilding(float RotationAmount)
{
	GameGrid->RotatePreviewObject(RotationAmount);
}

void AGameHUD::ShowBuildMenu()
{

	GameGrid->ToggleSelectionTile(true);
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

void AGameHUD::RemoveBuildMenu()
{
	//Reseting
	SelectedBuildMenuObject = nullptr;
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

//Sets actual Objects in game selected
void AGameHUD::SetGameObjectSelected(FHitResult Hit)
{
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
		SelectedObject = HitActor;
		if (ISelectInterface* Select = Cast<ISelectInterface>(HitActor)) {
			Select->SetSelected();
			SelectMenuWidget->AddToViewport();
		}
		else if (AItemActor* Item = Cast<AItemActor>(SelectedObject)) {
			if (Item->WidgetComponent) Item->WidgetComponent->SetVisibility(true);
		}
		else SelectMenuWidget->RemoveFromViewport();
	}
}


USelectMenuWidget* AGameHUD::GetSelectMenu() {
	return SelectMenuWidget;
}

