// Fill out your copyright notice in the Description page of Project Settings.
#include "ResourceBuildingActor.h"
#include "MainPlayerState.h"

AResourceBuildingActor::AResourceBuildingActor() {

}

void AResourceBuildingActor::BeginPlay()
{

	Super::BeginPlay();
	Gathering = true;
	GetWorldTimerManager().SetTimer(PrimaryResourceTimerHandle, this, &AResourceBuildingActor::ResourceInit, ResourceTick, false, ResourceTick);
}

void AResourceBuildingActor::ResourceInit()
{
	if (Gathering) {
		if (Upgrades.Contains(Level)) BuildingGatherResources(Upgrades[Level].Production);
		GetWorldTimerManager().SetTimer(PrimaryResourceTimerHandle, this, &AResourceBuildingActor::ResourceInit, ResourceTick, false, ResourceTick);
	}
}

void AResourceBuildingActor::GatherResources(int Gold, int Wood, int Stone, int Food) {
	PS->AddGold(Gold);
	PS->AddWood(Wood);
	PS->AddStone(Stone);
	PS->AddFood(Food);
}

void AResourceBuildingActor::BuildingGatherResources(FBuildingProduction Production) {
	PS->AddGold(Production.Gold);
	PS->AddWood(Production.Wood);
	PS->AddStone(Production.Stone);
	PS->AddFood(Production.Food);
}


void AResourceBuildingActor::GatherGold(int Gold)
{
	PS->AddGold(Gold);
}

void AResourceBuildingActor::GatherWood(int Wood)
{
	PS->AddWood(Wood);
}

void AResourceBuildingActor::GatherStone(int Stone)
{
	PS->AddStone(Stone);
}

void AResourceBuildingActor::GatherFood(int Food)
{
	PS->AddFood(Food);
}
