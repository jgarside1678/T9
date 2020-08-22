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
					OnInventoryUpdate.Broadcast();
					return true;
				}
			}
		}
	}
	//Inventory.Add(InventoryItem);
	return false;
}


bool UInventoryComponent::AddItemToInventorySlot(FSlot ItemSlot, AItemActor* Item)
{
	TSubclassOf<AItemActor> item_class = Item->GetClass();
	AItemActor* InventoryItem = NewObject<AItemActor>(this, item_class);
	int Index = ItemSlot.SlotID;
	if (Index < Inventory.Num() && !Inventory[Index].SlotUsed) {
		if (Item->GetItemType() == AnyType || Inventory[Index].SlotType == AnyType || Item->GetItemType() == Inventory[Index].SlotType) {
			if (Item->GetItemSubType() == AnySubType || Inventory[Index].SlotSubType == AnySubType || Item->GetItemSubType() == Inventory[Index].SlotSubType) {
				Inventory[Index].Item = InventoryItem;
				Inventory[Index].SlotUsed = true;
				Item->Destroy();
				OnInventoryUpdate.Broadcast();
				return true;
			}
		}
	}
	//Inventory.Add(InventoryItem);
	return false;
}

bool UInventoryComponent::RemoveItemFromInventory(int InventorySlot)
{
	if (Inventory.Num() >= InventorySlot) {
		Inventory[InventorySlot].Item = nullptr;
		Inventory[InventorySlot].SlotUsed = false;
		OnInventoryUpdate.Broadcast();
		return true;
	}
	return false;
}

bool UInventoryComponent::CheckForItemInInventory(AItemActor* Item, int& ItemIndex)
{
	for (int x = 0; x < Inventory.Num(); x++) {
		if (Inventory[x].Item == Item) {
			ItemIndex = x;
			return true;
		}
	}
	return false;
}

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
	FSlot NewSlot = FSlot{ InventorySlotCounter, Slot.SlotType, Slot.SlotSubType, Slot.Item, Slot.SlotUsed };
	if(Inventory.Num() < Capacity)	Inventory.Add(NewSlot);
	InventorySlotCounter++;
}

void UInventoryComponent::FillInventorySlots(FSlot Slot)
{
	for (int x = Inventory.Num(); x < Capacity; x++) {
		FSlot NewSlot = FSlot{ InventorySlotCounter, Slot.SlotType, Slot.SlotSubType, Slot.Item, Slot.SlotUsed };
		Inventory.Add(NewSlot);
		InventorySlotCounter++;
	}
}
