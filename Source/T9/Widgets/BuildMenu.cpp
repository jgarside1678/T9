// Fill out your copyright notice in the Description page of Project Settings.
#include "BuildMenu.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "T9/T9GameModeBase.h"

UBuildMenu::UBuildMenu(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BuildingsDataTableObject(TEXT("DataTable'/Game/DataTables/BuildingsMenu.BuildingsMenu'"));
	BuildMenuBuildings = BuildingsDataTableObject.Object;

}

void UBuildMenu::NativeConstruct()
{
	Super::NativeConstruct();

}


void UBuildMenu::RotateSelection()
{
	if (!PC) PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC->HUDPointer) PC->HUDPointer->RotateSelectedBuilding(90.0f);
}

