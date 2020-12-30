// Fill out your copyright notice in the Description page of Project Settings.


#include "Alliance_ResourceGatherer.h"
#include "T9/AI/Alliance_Gatherer_Controller.h"
#include "T9/MainPlayerState.h"
#include "T9/MainPlayerController.h"
#include "T9/Widgets/HealthBarWidget.h"

#include "T9/AI/AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BrainComponent.h"
#include "T9/BlackBoard_Keys.h"

AAlliance_ResourceGatherer::AAlliance_ResourceGatherer() {

	AIControllerClass = AAlliance_Gatherer_Controller::StaticClass();
	if(GatheringLevels.Num() == 0) GatheringLevels.Add(1, FGathererLevels{ 50, 100 });
}

void AAlliance_ResourceGatherer::GatherResources()
{
	IsGathering = true;
	EquipMainHand();
	if (GatheringLevels.Contains(Level)) {
		GatheredResource += GatherAmount;
		if (GatheredResource > MaxResourceInventory) GatheredResource = MaxResourceInventory;
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
	if (GatheredResource == GatheringLevels[Level].MaxResourceInventory) {
		IsGathering = false;
		SheathMainHand();
		return true;
	}
	return false;
}

int AAlliance_ResourceGatherer::GetGatherAmount()
{
	return GatherAmount;
}

int AAlliance_ResourceGatherer::GetMaxResourceInventory()
{
	return MaxResourceInventory;
}

FGathererLevels AAlliance_ResourceGatherer::GetGathererBaseStats()
{
	if (GatheringLevels.Contains(Level)) return GatheringLevels[Level];
	else return FGathererLevels();
}

FGathererLevels AAlliance_ResourceGatherer::GetGathererUpgradeStats()
{
	if (GatheringLevels.Contains(Level+1)) return GatheringLevels[Level+1];
	else if(GatheringLevels.Contains(Level)) return GatheringLevels[Level];
	else return FGathererLevels();
}

void AAlliance_ResourceGatherer::SetHuntTarget(AActor* NewTarget)
{
	Target = NewTarget;
	TargetInterface = Cast<IDamageInterface>(Target);
	if (Cont) {
		Cont->GetBlackboard()->SetValueAsObject(bb_keys::hunt, Target);
		if (Target) Cont->BrainComponent->RestartLogic();
	}
}

void AAlliance_ResourceGatherer::CalculateGatherAmount()
{
	GatherAmount = 0;
	if (GatheringLevels.Contains(Level)) GatherAmount += GatheringLevels[Level].GatherAmount;
	if (CurrentResource) GatherAmount *= CurrentResource->GetResourceStats().ResourceGatherMultiplier;
	GatherAmount += ItemModifiers.ProductionStats.ItemGatherBase;
	GatherAmount *= ItemModifiers.ProductionStats.ItemGatherMultiplier;
}

void AAlliance_ResourceGatherer::CalculateMaxResourceInventory()
{
	MaxResourceInventory = 0;
	if (GatheringLevels.Contains(Level)) MaxResourceInventory += GatheringLevels[Level].MaxResourceInventory;
}

void AAlliance_ResourceGatherer::SetResource(AResourceActor* Resource)
{
	CurrentResource = Resource;
	CalculateGatherAmount();
}

void AAlliance_ResourceGatherer::BaseCalculate()
{
	Super::BaseCalculate();
	CalculateGatherAmount();
	CalculateMaxResourceInventory();
}



void AAlliance_ResourceGatherer::Command(FHitResult Hit)
{
	IsGathering = false;
	Super::Command(Hit);

}

AResourceActor* AAlliance_ResourceGatherer::GetCommandedResourceActor()
{
	return CommandedResourceActor;
}

AResourceCharacter* AAlliance_ResourceGatherer::GetCommandedResourceCharacter()
{
	return CommandedResourceCharacter;
}
