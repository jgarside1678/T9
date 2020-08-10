// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySelect.h"
#include "T9/MainPlayerState.h"


UInventory::UInventory(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{
}

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventory::NativeOnInitialized()
{
	PC = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

	Super::NativeOnInitialized();
}