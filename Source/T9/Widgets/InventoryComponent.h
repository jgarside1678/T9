// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "T9/Items/ItemActor.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);





USTRUCT(BlueprintType)
struct FSlot {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<Type> SlotType = AnyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<SubType> SlotSubType = AnySubType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AItemActor* Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SlotUsed = false;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class T9_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		TArray<FSlot> Inventory;

	UPROPERTY()
		int Capacity = 1;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FOnInventoryUpdated OnInventoryUpdate;

	UFUNCTION(BlueprintCallable)
		bool AddItemToInventory(AItemActor* Item);

	UFUNCTION(BlueprintCallable)
		bool RemoveItemFromInventory(int InventorySlot);

	UFUNCTION(BlueprintCallable)
		bool CheckForItemInInventory(AItemActor* Item, int& ItemIndex);

	UFUNCTION(BlueprintCallable)
		TArray<FSlot> GetItems();

	UFUNCTION(BlueprintCallable)
		void SetCapacity(int Number);

	UFUNCTION(BlueprintCallable)
		int GetCapacity();

	UFUNCTION(BlueprintCallable)
		void AddInventorySlot(FSlot Slot);

	//Adds Inventory slots with given parameter untill inventory capacity is full.
	UFUNCTION(BlueprintCallable)
		void FillInventorySlots(FSlot Slot);

		
};


//
//
//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
//class T9_API UInventoryComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:
//	// Sets default values for this component's properties
//	UInventoryComponent();
//
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//	UPROPERTY(VisibleAnywhere)
//		TArray<AItemActor*> Inventory;
//
//	UPROPERTY()
//		int Capacity = 0;
//
//public:
//	// Called every frame
//	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//	UPROPERTY(BlueprintAssignable)
//		FOnInventoryUpdated OnInventoryUpdate;
//
//	UFUNCTION(BlueprintCallable)
//		bool AddItemToInventory(AItemActor* Item);
//
//	UFUNCTION(BlueprintCallable)
//		bool RemoveItemFromInventory(int InventorySlot);
//
//	UFUNCTION(BlueprintCallable)
//		bool CheckForItemInInventory(AItemActor* Item, int& ItemIndex);
//
//	UFUNCTION(BlueprintCallable)
//		TArray<AItemActor*> GetItems();
//
//
//};