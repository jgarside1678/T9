// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_SpecialAttack.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"

UAI_SpecialAttack::UAI_SpecialAttack(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("SpecialAttack Target");
}

EBTNodeResult::Type UAI_SpecialAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<ACharacterActor>(Cont->GetPawn());
	UObject* Target = Cont->GetBlackboard()->GetValueAsObject(bb_keys::combat_target);

	if (Target != nullptr && Target->IsValidLowLevel()) {
		AActor* TargetActor = (AActor*)Target;
		NPC->SpecialAttack(TargetActor);
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}