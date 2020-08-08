// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_DepositResources.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Characters/Alliance/Alliance_ResourceGatherer.h"
#include "T9/BlackBoard_Keys.h"

UAI_DepositResources::UAI_DepositResources(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Deposit Resources");
}

EBTNodeResult::Type UAI_DepositResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<AAlliance_ResourceGatherer>(Cont->GetPawn());
	NPC->DepositResources();
	Cont->GetBlackboard()->SetValueAsBool(bb_keys::inventory_is_full, false);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;


}
