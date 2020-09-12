// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_SetTargetAsHunt.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "T9/BlackBoard_Keys.h"

UAI_SetTargetAsHunt::UAI_SetTargetAsHunt(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Is Hunt Dead");
}

EBTNodeResult::Type UAI_SetTargetAsHunt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAI_Controller* Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	UObject* HuntTarget = Cont->GetBlackboard()->GetValueAsObject(bb_keys::hunt);
	Cont->GetBlackboard()->SetValueAsObject(bb_keys::target_actor, (UObject*)HuntTarget);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}