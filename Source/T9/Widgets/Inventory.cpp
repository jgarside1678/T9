// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "T9/GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "T9/MainPlayerState.h"

UInventory::UInventory(const FObjectInitializer& ObjectInit) :Super(ObjectInit)
{

}

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();
}
