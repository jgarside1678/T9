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
	for (int x = 0; x < Inventory.Num(); x++) {
		if (!Inventory[x].SlotUsed) {
			if (Item->GetItemType() == AnyType || Inventory[x].SlotType == AnyType || Item->GetItemType() == Inventory[x].SlotType) {
				if (Item->GetItemSubType() == AnySubType || Inventory[x].SlotSubType == AnySubType || Item->GetItemSubType() == Inventory[x].SlotSubType) {
					Inventory[x].Item = InventoryItem;
					Inventory[x].SlotUsed = true;
					Item->Destroy();
					break;
				}
				else{}
			}
		}
	}
	//Inventory.Add(InventoryItem);
	OnInventoryUpdate.Broadcast();
	return true;
}

//bool UInventoryComponent::RemoveItemFromInventory(int InventorySlot)
//{
//	if (Inventory.Num() >= InventorySlot) {
//		Inventory.RemoveAt(InventorySlot);
//		OnInventoryUpdate.Broadcast();
//		return true;
//	}
//	return false;
//}
//
//bool UInventoryComponent::CheckForItemInInventory(AItemActor* Item, int& ItemIndex)
//{
//	if (Inventory.Contains(Item)) {
//		ItemIndex = Inventory.IndexOfByKey(Item);
//		return true;
//	}
//	return false;
//}

TArray<FSlot> UInventoryComponent::GetItems()
{
	return Inventory;
}

void UInventoryComponent::SetCapacity(int Number)
{
	Capacity = Number;
}

int UInventoryComponent::GetCapacity()
{
	return Capacity;
}

void UInventoryComponent::AddInventorySlot(FSlot Slot)
{
	if(Inventory.Num() < Capacity)	Inventory.Add(Slot);
}



//
//#include "InventoryComponent.h"
//
//// Sets default values for this component's properties
//UInventoryComponent::UInventoryComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UInventoryComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//
//}
//
//
//// Called every frame
////void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
////{
////	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
////
////	// ...
////}
//
//
//bool UInventoryComponent::AddItemToInventory(AItemActor* Item)
//{
//	TSubclassOf<AItemActor> item_class = Item->GetClass();
//	AItemActor* InventoryItem = NewObject<AItemActor>(this, item_class);
//	Inventory.Add(InventoryItem);
//	Item->Destroy();
//	OnInventoryUpdate.Broadcast();
//	return true;
//}
//
//bool UInventoryComponent::RemoveItemFromInventory(int InventorySlot)
//{
//	if (Inventory.Num() >= InventorySlot) {
//		Inventory.RemoveAt(InventorySlot);
//		OnInventoryUpdate.Broadcast();
//		return true;
//	}
//	return false;
//}
//
//bool UInventoryComponent::CheckForItemInInventory(AItemActor* Item, int& ItemIndex)
//{
//	if (Inventory.Contains(Item)) {
//		ItemIndex = Inventory.IndexOfByKey(Item);
//		return true;
//	}
//	return false;
//}
//
//TArray<AItemActor*> UInventoryComponent::GetItems()
//{
//	return Inventory;
//}
