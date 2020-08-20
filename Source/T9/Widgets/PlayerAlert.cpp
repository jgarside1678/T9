// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAlert.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
#include "LevelUpItem.h"
#include "Components/WrapBox.h"
#include "TimerManager.h"
#include "T9/MainPlayerState.h"

UPlayerAlert::UPlayerAlert(const FObjectInitializer& ObjectInit) : Super(ObjectInit) {

}

void UPlayerAlert::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerAlert::NativePreConstruct()
{
	if (!PC) 	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	if (PC) {
		GameHUD = Cast<AGameHUD>(PC->GetHUD());
		PS = Cast<AMainPlayerState>(PC->PlayerState);
	}
	Super::NativePreConstruct();
}

void UPlayerAlert::SetAlertContent(FString Title, FString Message)
{
	TitleText->SetText(FText::FromString(Title));
	MessageText->SetText(FText::FromString(Message));
}
