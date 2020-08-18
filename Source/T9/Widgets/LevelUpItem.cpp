// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"

ULevelUpItem::ULevelUpItem(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
}


void ULevelUpItem::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULevelUpItem::NativeOnInitialized()
{

	//PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	//HUD = Cast<AGameHUD>(PC->GetHUD());
	Super::NativeOnInitialized();
}

void ULevelUpItem::Init(UTexture2D* Image, int Amount)
{
	ItemImage->SetBrushFromTexture(Image);
	ItemAmount->SetText(FText::FromString(FString::FromInt(Amount)));
}
