// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUp.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
#include "LevelUpItem.h"
#include "Components/WrapBox.h"
#include "T9/MainPlayerState.h"

ULevelUp::ULevelUp(const FObjectInitializer& ObjectInit) : Super(ObjectInit)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemBP(TEXT("WidgetBlueprint'/Game/UI/LevelUpItem_BP.LevelUpItem_BP_C'"));
	if (ItemBP.Succeeded()) {
		ItemClass = ItemBP.Class;
	}
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
	NewItemsBox->ClearChildren();
	NewLevel->SetText(FText::FromString(FString::FromInt(Level)));
}

void ULevelUp::CreatePreviewWidget(UTexture2D* Image, int Amount)
{
	ULevelUpItem* NewItem = Cast<ULevelUpItem>(CreateWidget(NewItemsBox, ItemClass));
	NewItem->Init(Image, Amount);
	NewItemsBox->AddChild(NewItem);
}
