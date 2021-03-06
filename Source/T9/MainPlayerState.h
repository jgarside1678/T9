// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "T9/Actors/Terrain/TerrainActor.h"
#include "T9/Characters/CharacterActor.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRankChange);


UENUM(BlueprintType)
enum Rank
{
	Peasent UMETA(DisplayName = "Peasent"),
	Esquire UMETA(DisplayName = "Esquire/Esquiress"),
	Knight UMETA(DisplayName = "Knight/Lady"),
	Baron UMETA(DisplayName = "Baron/Baroness"),
	Viscount UMETA(DisplayName = "Viscount/Viscountess"),
	Earl UMETA(DisplayName = "Earl/Countess"),
	Marquess UMETA(DisplayName = "Marquess/Marchinoness"),
	Duke UMETA(DisplayName = "Duke/Duchess"),
	Prince UMETA(DisplayName = "Prince/Princess"),
	King UMETA(DisplayName = "King/Queen"),
	Emperor UMETA(DisplayName = "Emperor/Emperoress")
};

USTRUCT(BlueprintType)
struct FBuildingCounts {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int BuildingCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int BuildingStorageCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int BuildingMaxCount = 1;

};

USTRUCT(BlueprintType)
struct FBuildingCountsIncrease {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* PreviewImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int BuildingMaxCountIncrease = 1;

};

USTRUCT(BlueprintType)
struct FPlayerLevelUpgrades : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBuildingCountsIncrease> BuildingIncreases;

};


UCLASS()
class T9_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

		AMainPlayerState();

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		class AGameHUD* HUD;

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
		int Power = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<Rank> CurrentRank = Peasent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
		TMap<TEnumAsByte<Rank>, int> RankThresholds = { {Peasent, 0}, {Esquire, 250}, {Knight, 700} , {Baron, 1400} , {Viscount, 2100},{Earl, 3500} ,{Marquess, 5200} ,{Duke, 7500} ,{Prince, 11000} ,{King, 15000} ,{Emperor, 25000} };

	UPROPERTY()
	    float CurrentXP = 0;

	UPROPERTY()
	    float RequiredXP = 100;

	UPROPERTY()
		TMap<FString, FBuildingCounts> BuildingCounts = { {"Town Hall", FBuildingCounts{0, 0, 1}}, {"Arrow Tower", FBuildingCounts{0, 0, 3}}, {"Wizards Tower", FBuildingCounts{0, 0, 100}}};

	UPROPERTY()
		class UDataTable* PlayerLevels;

	TArray<FPlayerLevelUpgrades*> PlayerLevelsArray;

	//UPROPERTY()
	//	TMap<FString, int> Building_Count = { {"Town Hall", 0}, {"Arrow Tower", 0}, {"Wizards Tower", 0} };

	//UPROPERTY()
	//	TMap<FString, int> Building_MaxCount = { {"Town Hall", 231}, {"Arrow Tower", 400}, {"Wizards Tower", 3} };

	UPROPERTY(VisibleAnywhere)
		class UInventoryComponent* InventoryComponent;

public:

	UPROPERTY(BlueprintAssignable)
		FOnRankChange RankChange;

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

	UFUNCTION(Category = "PlayerInfo")
		bool AddResources(FBuildingCosts Cost);

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

	//Level and XP

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

	UFUNCTION(BlueprintCallable)
		bool CheckXP();

	UFUNCTION(BlueprintCallable)
		void LevelUp();

	//Power

	UFUNCTION(BlueprintCallable)
		int GetPower();

	UFUNCTION(BlueprintCallable)
		void AddPower(int Amount);

	UFUNCTION(BlueprintCallable)
		void UpdateRank();

	UFUNCTION(BlueprintCallable)
		void ChangeRank(Rank NewRank);

	UFUNCTION(BlueprintCallable)
	    Rank GetRank();

	UFUNCTION(BlueprintCallable)
		int GetNextRankPower();



	//Building Counts

	UFUNCTION(BlueprintCallable)
		int GetBuildingCount(FString Name);

	UFUNCTION(BlueprintCallable)
		int GetBuildingStorageCount(FString Name);

	UFUNCTION(BlueprintCallable)
		int GetMaxBuildingCount(FString Name);

	UFUNCTION(BlueprintCallable)
		void SetBuildingCount(FString Name, int Number);

	UFUNCTION(BlueprintCallable)
		void SetBuildingStorageCount(FString Name, int Number);

	UFUNCTION(BlueprintCallable)
		void SetMaxBuildingCount(FString Name, int Number);

	//INVENTORY -----------------------

	UFUNCTION(BlueprintCallable)
		class UInventoryComponent* GetInventory();


};
