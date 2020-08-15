// Fill out your copyright notice in the Description page of Project Settings.
#include "AI_AttackTarget.h"
#include "AI_Controller.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"

UAI_AttackTarget::UAI_AttackTarget(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Attack Target");
}

EBTNodeResult::Type UAI_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<ACharacterActor>(Cont->GetPawn());
	UObject* Target = Cont->GetBlackboard()->GetValueAsObject(bb_keys::target_actor);
	if (Target != nullptr && Target->IsValidLowLevel() && !NPC->IsDead) {
		AActor* TargetActor = (AActor*)Target;
		if (ABuildingActor* Building = Cast<ABuildingActor>(TargetActor)) {
			if (Building->GetDisabled()) {
				Cont->GetBlackboard()->SetValueAsObject(bb_keys::target_actor, nullptr);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		if(LastAttackHasFinnished(NPC)) NPC->Attack(TargetActor, AttackNumber);
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

bool UAI_AttackTarget::LastAttackHasFinnished(ACharacterActor* NPC) {
	return !NPC->GetMesh()->GetAnimInstance()->Montage_IsPlaying(NPC->CurrentMontage);
}