// Fill out your copyright notice in the Description page of Project Settings.
#include "BuildMenu.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Actors/GameGridActor.h"
#include "T9/T9GameModeBase.h"

UBuildMenu::UBuildMenu(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BuildingsDataTableObject(TEXT("DataTable'/Game/DataTables/BuildingsMenu.BuildingsMenu'"));
	BuildMenuBuildings = BuildingsDataTableObject.Object;

}

void UBuildMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if (!PC) PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}


void UBuildMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UWorld* thing = GetWorld();
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();

}


void UBuildMenu::NativePreConstruct()
{
	if (!PC) PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	if (PC) HUD = Cast<AGameHUD>(PC->GetHUD());
	Super::NativePreConstruct();
}

void UBuildMenu::RotateSelection()
{
	if (HUD) HUD->RotateSelectedBuilding(90.0f);
}

