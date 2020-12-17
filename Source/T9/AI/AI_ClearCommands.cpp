// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_ClearCommands.h"
#include "AI_Controller.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"

UAI_ClearCommands::UAI_ClearCommands(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Clear Commands");
}

EBTNodeResult::Type UAI_ClearCommands::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<ACharacterActor>(Cont->GetPawn());
	Cont->GetBlackboard()->ClearValue(bb_keys::command_location);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

