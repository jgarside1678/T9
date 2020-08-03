// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPlayerState.h"
#include "BuildingActor.h"
#include "Building_TownHall.h"

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
	SetCurrentXP(temp);
	SetRequiredXp(Level * 100);
	if (Level == 3) Building_MaxCount["Arrow Tower"] += 1;
	//Do Level up things;
}


int AMainPlayerState::GetBuildingCount(FString Name) {
	if (Building_Count.Contains(Name)) 	return Building_Count[Name];
	else return 0;
}

int AMainPlayerState::GetMaxBuildingCount(FString Name) {
	if (Building_MaxCount.Contains(Name)) 	return Building_MaxCount[Name];
	else return 1;
}

void AMainPlayerState::SetBuildingCount(FString Name, int Number) {
	if (Building_Count.Contains(Name))  Building_Count[Name] = Number;
}

void AMainPlayerState::SetMaxBuildingCount(FString Name, int Number) {
	if (Building_MaxCount.Contains(Name))  Building_MaxCount[Name] = Number;
}

bool AMainPlayerState::AddItemToInventory(AItemActor* Item)
{
	AItemActor* InventoryItem = NewObject<AItemActor>(Item->GetClass());
	Inventory.Add(InventoryItem);
	Item->Destroy();
	return true;
}

bool AMainPlayerState::RemoveItemFromInventory(int InventorySlot)
{
	if (Inventory.Num() >= InventorySlot) {
		Inventory.RemoveAt(InventorySlot);
		return true;
	}
	return false;
}

bool AMainPlayerState::CheckForItemInInventory(AItemActor* Item, int& ItemIndex)
{
	if (Inventory.Contains(Item)) {
		ItemIndex = Inventory.IndexOfByKey(Item);
		return true;
	}
	return false;
}
