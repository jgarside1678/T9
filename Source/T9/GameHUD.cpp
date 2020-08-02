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


AGameHUD::AGameHUD() {

	static ConstructorHelpers::FObjectFinder<UDataTable> BuildingsDataTableObject(TEXT("DataTable'/Game/DataTables/BuildingsMenu.BuildingsMenu'"));
	BuildMenuBuildings = BuildingsDataTableObject.Object;


	static ConstructorHelpers::FClassFinder<UUserWidget> Widget1(TEXT("WidgetBlueprint'/Game/UI/BuildMenu.BuildMenu_C'"));
	BuildMenuClass = Widget1.Class;
	if (BuildMenuClass)
	{
		BuildMenuWidget = CreateWidget<UBuildMenuWidget>(GetWorld(), BuildMenuClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> Widget2(TEXT("WidgetBlueprint'/Game/UI/HUDMenu.HUDMenu_C'"));
	HUDMenuClass = Widget2.Class;
	if (HUDMenuClass)
	{
		HUDMenuWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDMenuClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> Widget3(TEXT("WidgetBlueprint'/Game/UI/SelectMenu.SelectMenu_C'"));
	if (Widget3.Succeeded()) SelectMenuWidget = CreateWidget<USelectMenuWidget>(GetWorld(), Widget3.Class);


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
			GameGrid->ScaleSelectionTile(SelectedBuildMenuObject->BuildingHeightX, SelectedBuildMenuObject->BuildingWidthY);
			PreviewBuilding = GameGrid->CreatePreviewObject(*SelectedBuildMenuObject);
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

