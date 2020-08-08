// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "T9/Actors/Terrain/TerrainActor.h"
#include "T9/Characters/CharacterActor.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"
/**
 * 
 */


UCLASS()
class T9_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

		AMainPlayerState();

private:

	UPROPERTY()
	    int Gold = 100000;

	UPROPERTY()
		int Wood = 10000;

	UPROPERTY()
		int Stone = 10000;

	UPROPERTY()
		int Food = 10000;

	UPROPERTY()
	    int Level = 1;

	UPROPERTY()
	    float CurrentXP = 0;

	UPROPERTY()
	    float RequiredXP = 100;

	UPROPERTY()
		TMap<FString, int> Building_Count = { {"Town Hall", 0}, {"Arrow Tower", 0} };

	UPROPERTY()
		TMap<FString, int> Building_MaxCount = { {"Town Hall", 231}, {"Arrow Tower", 400} };;

	UPROPERTY(VisibleAnywhere)
		class UInventoryComponent* InventoryComponent;

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<ABuildingActor*> SpawnedBuildings;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<AResourceActor*> SpawnedResources;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<ACharacterActor*> SpawnedEnemyCharacters;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<ACharacterActor*> SpawnedAllianceCharacters;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<ATerrainActor*> SpawnedTerrain;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<ABuildingActor*> SpawnedWalls;

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void BuildingArrayClean();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void ResourceArrayClean();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		bool ResourceCheckSeperate(int G, int W = 0, int S = 0, int F = 0);

	UFUNCTION(Category = "PlayerInfo")
		bool ResourceCheck(FBuildingCosts Cost);

	UFUNCTION(Category = "PlayerInfo")
		bool RemoveResources(FBuildingCosts Cost);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	    void SetGold(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	    void AddGold(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	    int GetGold();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void SetWood(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void AddWood(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		int GetWood();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void SetStone(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void AddStone(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		int GetStone();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void SetFood(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void AddFood(int Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		int GetFood();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	    void SetLevel(int Number);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	    void AddLevel(int Number);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	    int GetLevel();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void SetRequiredXp(float Number);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		float GetRequiredXP();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void SetCurrentXP(float Number);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		float GetCurrentXP();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		void AddCurrentXP(float Number);

	UFUNCTION()
		bool CheckXP();

	UFUNCTION()
		void LevelUp();

	UFUNCTION()
		int GetBuildingCount(FString Name);

	UFUNCTION()
		int GetMaxBuildingCount(FString Name);

	UFUNCTION()
		void SetBuildingCount(FString Name, int Number);

	UFUNCTION()
		void SetMaxBuildingCount(FString Name, int Number);

	//INVENTORY -----------------------

	UFUNCTION(BlueprintCallable)
		class UInventoryComponent* GetInventory();

	//UPROPERTY()
	//	int Capacity = 0;

	//UPROPERTY(BlueprintAssignable)
	//	FOnInventoryUpdated OnInventoryUpdate;

	//UFUNCTION(BlueprintCallable)
	//	bool AddItemToInventory(AItemActor* Item);

	//UFUNCTION(BlueprintCallable)
	//	bool RemoveItemFromInventory(int InventorySlot);

	//UFUNCTION(BlueprintCallable)
	//	bool CheckForItemInInventory(AItemActor* Item, int& ItemIndex);

	//UFUNCTION(BlueprintCallable)
	//	TArray<AItemActor*> GetInventory();

};
