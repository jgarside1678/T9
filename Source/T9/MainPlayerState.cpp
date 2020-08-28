// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPlayerState.h"
#include "T9/Actors/Components/InventoryComponent.h"
#include "MainPlayerController.h"
#include "T9/Widgets/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Widgets/LevelUp.h"
#include "T9/Actors/Buildings/Building_TownHall.h"


AMainPlayerState::AMainPlayerState()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	InventoryComponent->SetCapacity(32);
	InventoryComponent->FillInventorySlots(FSlot{});

	static ConstructorHelpers::FObjectFinder<UDataTable> Levels(TEXT("DataTable'/Game/DataTables/PlayerLevels.PlayerLevels'"));
	if (Levels.Succeeded()) {
		PlayerLevels = Levels.Object;
		const TCHAR* Context = new TCHAR('Q');
		PlayerLevels->GetAllRows(Context, PlayerLevelsArray);
	}
}


void AMainPlayerState::BeginPlay()
{
	PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	HUD = Cast<AGameHUD>(PC->GetHUD());
}

void AMainPlayerState::BuildingArrayClean()
{
	for (int x = 0; x < SpawnedBuildings.Num(); x++) {
		if (SpawnedBuildings[x] == nullptr) SpawnedBuildings.RemoveAt(x, 1, false);
	}
}

void AMainPlayerState::ResourceArrayClean()
{
	for (int x = 0; x < SpawnedResources.Num(); x++) {
		if (SpawnedResources[x] == nullptr) SpawnedResources.RemoveAt(x, 1, false);
	}
}

bool AMainPlayerState::ResourceCheckSeperate(int G, int W, int S, int F)
{
	if (G <= Gold && W <= Wood && S <= Stone && F <= Food) return true;
	return false;
}

bool AMainPlayerState::ResourceCheck(FBuildingCosts Cost)
{
	if (Cost.Gold <= Gold && Cost.Wood <= Wood && Cost.Stone <= Stone && Cost.Food <= Food) return true;
	return false;
}

bool AMainPlayerState::RemoveResources(FBuildingCosts Cost)
{
	if (Cost.Gold <= Gold && Cost.Wood <= Wood && Cost.Stone <= Stone && Cost.Food <= Food) {
		Gold -= Cost.Gold;
		Wood -= Cost.Wood;
		Stone -= Cost.Stone;
		Food -= Cost.Food;
		return true;
	}
	return false;
}

bool AMainPlayerState::AddResources(FBuildingCosts Cost)
{
	Gold += Cost.Gold;
	Wood += Cost.Wood;
	Stone += Cost.Stone;
	Food += Cost.Food;
	return true;
}

void AMainPlayerState::SetGold(int Amount)
{
	Gold = Amount;
}

void AMainPlayerState::AddGold(int Amount)
{
	Gold += Amount;
}

int AMainPlayerState::GetGold()
{
	return Gold;
}

void AMainPlayerState::SetWood(int Amount)
{
	Wood = Amount;
}

void AMainPlayerState::AddWood(int Amount)
{
	Wood += Amount;
}

int AMainPlayerState::GetWood()
{
	return Wood;
}

void AMainPlayerState::SetStone(int Amount)
{
	Stone = Amount;
}

void AMainPlayerState::AddStone(int Amount)
{
	Stone += Amount;
}

int AMainPlayerState::GetStone()
{
	return Stone;
}

void AMainPlayerState::SetFood(int Amount)
{
	Food = Amount;
}

void AMainPlayerState::AddFood(int Amount)
{
	Food += Amount;
}

int AMainPlayerState::GetFood()
{
	return Food;
}

void AMainPlayerState::SetLevel(int Number)
{
	Level = Number;
}

void AMainPlayerState::AddLevel(int Number)
{
	Level += Number;
}

int AMainPlayerState::GetLevel()
{
	return Level;
}

void AMainPlayerState::SetRequiredXp(float Number)
{
	RequiredXP = Number;
}

float AMainPlayerState::GetRequiredXP()
{
	return RequiredXP;
}

void AMainPlayerState::SetCurrentXP(float Number)
{
	CurrentXP = Number;
	CheckXP();
}

float AMainPlayerState::GetCurrentXP()
{
	return CurrentXP;
}

void AMainPlayerState::AddCurrentXP(float Number)
{
	CurrentXP += Number;
	CheckXP();
}

bool AMainPlayerState::CheckXP() {
	if (CurrentXP >= RequiredXP) {
		LevelUp();
		return true;
	}
	return false;
}

void AMainPlayerState::LevelUp() {
	float temp = CurrentXP - RequiredXP;
	Level += 1;
	HUD->PlayerLevelUp(Level);
	SetCurrentXP(temp);
	SetRequiredXp(Level * 100);
	if (PlayerLevelsArray.Num() >= Level) {
		for (int x = 0; x < PlayerLevelsArray[Level-1]->BuildingIncreases.Num(); x++) {
			if (PlayerLevelsArray[Level - 1] && BuildingCounts.Contains(PlayerLevelsArray[Level - 1]->BuildingIncreases[x].BuildingName)) {
				BuildingCounts[PlayerLevelsArray[Level - 1]->BuildingIncreases[x].BuildingName].BuildingMaxCount += PlayerLevelsArray[Level - 1]->BuildingIncreases[x].BuildingMaxCountIncrease;
				HUD->GetLevelUpWidget()->CreatePreviewWidget(PlayerLevelsArray[Level - 1]->BuildingIncreases[x].PreviewImage, PlayerLevelsArray[Level - 1]->BuildingIncreases[x].BuildingMaxCountIncrease);
			}
		}
	}
	//if (Level == 3) BuildingCounts["Arrow Tower"] += 1;
	//Do Level up things;
}

int AMainPlayerState::GetPower()
{
	return Power;
}

void AMainPlayerState::AddPower(int Amount)
{
	Power += Amount;
	UpdateRank();
}

void AMainPlayerState::UpdateRank()
{
	if (RankThresholds.Contains(CurrentRank)) {
		int Index = TEnumAsByte<Rank>(CurrentRank);
		if (RankThresholds[CurrentRank] <= Power) {
			for (int x = Index; x < 11; x++) {
				Index++;
				if (RankThresholds.Contains((Rank)Index)) {
					if (RankThresholds[(Rank)Index] > Power) break;
					else CurrentRank = (Rank)Index;
				}
				else break;
			}
		}
		else {
			for (int x = Index; x >= 0; x--) {
				Index--;
				if (RankThresholds.Contains((Rank)Index)) {
					CurrentRank = (Rank)Index;
					if (RankThresholds[(Rank)Index] <= Power) break;
				}
				else break;
			}
		}
		RankChange.Broadcast();
	}
}

void AMainPlayerState::ChangeRank(Rank NewRank)
{
	CurrentRank = NewRank;
}

Rank AMainPlayerState::GetRank()
{
	return CurrentRank;
}

int AMainPlayerState::GetNextRankPower()
{
	int Index = TEnumAsByte<Rank>(CurrentRank);
	Index++;
	if (RankThresholds.Contains((Rank)Index)) return RankThresholds[(Rank)Index];
	return 1;
}


int AMainPlayerState::GetBuildingCount(FString Name) {
	if (BuildingCounts.Contains(Name)) 	return BuildingCounts[Name].BuildingCount;
	else return 0;
}

int AMainPlayerState::GetBuildingStorageCount(FString Name)
{
	if (BuildingCounts.Contains(Name)) 	return BuildingCounts[Name].BuildingStorageCount;
	else return 0;
}

int AMainPlayerState::GetMaxBuildingCount(FString Name) {
	if (BuildingCounts.Contains(Name)) 	return BuildingCounts[Name].BuildingMaxCount;
	else return 1;
}

void AMainPlayerState::SetBuildingCount(FString Name, int Number) {
	if (BuildingCounts.Contains(Name))  BuildingCounts[Name].BuildingCount = Number;
}

void AMainPlayerState::SetBuildingStorageCount(FString Name, int Number)
{
	if (BuildingCounts.Contains(Name))  BuildingCounts[Name].BuildingStorageCount = Number;
}

void AMainPlayerState::SetMaxBuildingCount(FString Name, int Number) {
	if (BuildingCounts.Contains(Name))  BuildingCounts[Name].BuildingMaxCount = Number;
}

UInventoryComponent* AMainPlayerState::GetInventory()
{
	return InventoryComponent;
}



