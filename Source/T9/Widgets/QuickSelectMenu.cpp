// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSelectMenu.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Components/Button.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "SelectMenuWidget.h"

UQuickSelectMenu::UQuickSelectMenu(const FObjectInitializer& ObjectInit) : Super(ObjectInit) {

}

void UQuickSelectMenu::Init(AActor* Selected)
{
	SelectedBuilding = Cast<ABuildingActor>(Selected);
	SelectedResource = Cast<AResourceActor>(Selected);
}

void UQuickSelectMenu::MoveBuilding()
{
	this->RemoveFromViewport();
}

void UQuickSelectMenu::UpgradeRestoreBuilding()
{
	if (SelectedBuilding) {
		if (SelectedBuilding->GetDisabled()) SelectedBuilding->RestoreBuilding();
		else SelectedBuilding->Upgrade();
	}
	if (HUD)HUD->SetGameObjectSelected(FHitResult());
	this->RemoveFromViewport();
}

void UQuickSelectMenu::InfoBuilding()
{
	if (HUD) {
		HUD->ShowSelectMenu();
	}
	this->RemoveFromViewport();
}

void UQuickSelectMenu::StoreBuilding()
{
	if (SelectedBuilding) {
		SelectedBuilding->RemoveBuilding();
	}
	if (HUD)HUD->SetGameObjectSelected(FHitResult());
	this->RemoveFromViewport();
}

void UQuickSelectMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UQuickSelectMenu::NativePreConstruct() {
	if (!PC) 	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	if (PC) {
		HUD = Cast<AGameHUD>(PC->GetHUD());
		PS = Cast<AMainPlayerState>(PC->PlayerState);
	}
	Super::NativePreConstruct();
}