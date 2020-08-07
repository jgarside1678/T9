// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
//void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}


bool UInventoryComponent::AddItemToInventory(AItemActor* Item)
{
	TSubclassOf<AItemActor> item_class = Item->GetClass();
	AItemActor* InventoryItem = NewObject<AItemActor>(this, item_class);
	Inventory.Add(InventoryItem);
	Item->Destroy();
	OnInventoryUpdate.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItemFromInventory(int InventorySlot)
{
	if (Inventory.Num() >= InventorySlot) {
		Inventory.RemoveAt(InventorySlot);
		OnInventoryUpdate.Broadcast();
		return true;
	}
	return false;
}

bool UInventoryComponent::CheckForItemInInventory(AItemActor* Item, int& ItemIndex)
{
	if (Inventory.Contains(Item)) {
		ItemIndex = Inventory.IndexOfByKey(Item);
		return true;
	}
	return false;
}

TArray<AItemActor*> UInventoryComponent::GetItems()
{
	return Inventory;
}
