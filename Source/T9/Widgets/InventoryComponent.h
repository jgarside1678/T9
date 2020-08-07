// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "T9/ItemActor.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

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
		TArray<AItemActor*> Inventory;

	UPROPERTY()
		int Capacity = 0;

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
		TArray<AItemActor*> GetItems();

		
};
