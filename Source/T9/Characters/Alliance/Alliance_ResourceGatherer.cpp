// Fill out your copyright notice in the Description page of Project Settings.


#include "Alliance_ResourceGatherer.h"
#include "Alliance_Gatherer_Controller.h"
#include "T9/MainPlayerState.h"
#include "T9/MainPlayerController.h"
#include "T9/Widgets/HealthBarWidget.h"

AAlliance_ResourceGatherer::AAlliance_ResourceGatherer() {

	AIControllerClass = AAlliance_Gatherer_Controller::StaticClass();
	if(Upgrades.Num() == 0) Upgrades.Add(1, FGathererUpgrades{ 50, 100, 200, 10 });
}

void AAlliance_ResourceGatherer::GatherResources()
{
	IsGathering = true;
	EquipMainHand();
	if (Upgrades.Contains(Level)) {
		GatheredResource += Upgrades[Level].GatherAmount;
		if (GatheredResource > Upgrades[Level].MaxResourceInventory) GatheredResource = Upgrades[Level].MaxResourceInventory;
	}
}

void AAlliance_ResourceGatherer::DepositResources()
{
	IsGathering = false;
	switch (ResourceGatherType) {
	case Wood:
		PS->AddWood(GatheredResource);
		break;
	case Stone:
		PS->AddStone(GatheredResource);
		break;
	case Food:
		PS->AddFood(GatheredResource);
		break;
	default:
		break;
	}
	GatheredResource = 0;
}


bool AAlliance_ResourceGatherer::CheckFullInventory()
{
	if (GatheredResource == Upgrades[Level].MaxResourceInventory) {
		IsGathering = false;
		SheathMainHand();
		return true;
	}
	return false;
}

FGathererUpgrades AAlliance_ResourceGatherer::GetCurrentBaseStats()
{
	if (Upgrades.Contains(Level)) return Upgrades[Level];
	else return FGathererUpgrades();
}

FGathererUpgrades AAlliance_ResourceGatherer::GetUpgradeBaseStats()
{
	if (Upgrades.Contains(Level+1)) return Upgrades[Level+1];
	else if(Upgrades.Contains(Level)) return Upgrades[Level];
	else return FGathererUpgrades();
}

