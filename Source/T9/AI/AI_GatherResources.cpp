// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_GatherResources.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Characters/Alliance/Alliance_ResourceGatherer.h"
#include "T9/BlackBoard_Keys.h"

UAI_GatherResources::UAI_GatherResources(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Gather Resources");
}

EBTNodeResult::Type UAI_GatherResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<AAlliance_ResourceGatherer>(Cont->GetPawn());
	if (NPC) {
		NPC->GatherResources();
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

