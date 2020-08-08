// Fill out your copyright notice in the Description page of Project Settings.
#include "BuildMenuWidget.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "T9/T9GameModeBase.h"

UBuildMenuWidget::UBuildMenuWidget(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{

}

void UBuildMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBuildMenuWidget::SelectBuilding(FString Selection)
{
	if(!PC) PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC->HUDPointer) {
		PC->HUDPointer->SetSelectedBuildMenuObject(Selection);
	}
}

void UBuildMenuWidget::RotateSelection()
{
	if (!PC) PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC->HUDPointer) PC->HUDPointer->RotateSelectedBuilding(90.0f);
}

