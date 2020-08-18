// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUp.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "T9/MainPlayerState.h"

ULevelUp::ULevelUp(const FObjectInitializer& ObjectInit) : Super(ObjectInit)
{

}

void ULevelUp::NativeConstruct()
{

	Super::NativeConstruct();
}


void ULevelUp::NativePreConstruct() {
	if (!PC) 	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	if (PC) {
		GameHUD = Cast<AGameHUD>(PC->GetHUD());
		PS = Cast<AMainPlayerState>(PC->PlayerState);
	}
	Super::NativePreConstruct();
}


void ULevelUp::LevelUpInit(int Level)
{
	NewLevel->SetText(FText::FromString(FString::FromInt(Level)));
}
