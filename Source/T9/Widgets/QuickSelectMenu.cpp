// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSelectMenu.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "SelectMenuWidget.h"

UQuickSelectMenu::UQuickSelectMenu(const FObjectInitializer& ObjectInit) : Super(ObjectInit) {
	static ConstructorHelpers::FObjectFinder<UTexture2D> SpriteRestore(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_hammer.btn_icon_hammer'"));
	if (SpriteRestore.Succeeded()) {
		RestoreImage = SpriteRestore.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> SpriteUpgrade(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/19_Function_Button/ButtonIcon/128x128/btn_icon_arrow_up.btn_icon_arrow_up'"));
	if (SpriteUpgrade.Succeeded()) {
		UpgradeImage = SpriteUpgrade.Object;
	}
}

void UQuickSelectMenu::Init(ABuildingActor* Building)
{
	if (Building) {
		SelectedBuilding = Building;
		if(SelectedBuilding->GetDisabled()) RestoreUpgradeImage->SetBrushFromTexture(RestoreImage);
		else RestoreUpgradeImage->SetBrushFromTexture(UpgradeImage);
	}
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

void UQuickSelectMenu::SetRestoreImage()
{
	RestoreUpgradeImage->SetBrushFromTexture(RestoreImage);
}

void UQuickSelectMenu::SetUpgradeImage()
{
	RestoreUpgradeImage->SetBrushFromTexture(UpgradeImage);
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