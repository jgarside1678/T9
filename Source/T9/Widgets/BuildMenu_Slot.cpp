// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMenu_Slot.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Actors/GameGridActor.h"
#include "T9/T9GameModeBase.h"

UBuildMenu_Slot::UBuildMenu_Slot(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{

}

void UBuildMenu_Slot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBuildMenu_Slot::NativeOnInitialized()
{
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	HUD = Cast<AGameHUD>(PC->GetHUD());
	Super::NativeOnInitialized();
}

//bool UBuildMenu_Slot::Initialize()
//{
//	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
//	PS = (AMainPlayerState*)PC->PlayerState;
//	HUD = Cast<AGameHUD>(PC->GetHUD());
//	Super::Initialize();
//	return true;
//}

//void UBuildMenu_Slot::OnInitialized()
//{
//	Super::OnInitialized();
//	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
//	PS = (AMainPlayerState*)PC->PlayerState;
//	HUD = Cast<AGameHUD>(PC->GetHUD());
//}


