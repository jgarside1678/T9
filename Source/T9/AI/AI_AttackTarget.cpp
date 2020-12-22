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
	UObject* TargetObject = Cont->GetBlackboard()->GetValueAsObject(BlackboardKey.SelectedKeyName);
	AActor* Target = Cast<AActor>(TargetObject);
	if (Target != nullptr && Target->IsValidLowLevel() && !NPC->IsDead) {
		Cont->GetBlackboard()->SetValueAsFloat(bb_keys::attack_interval, NPC->GetAttackInterval());
		if (ABuildingActor* Building = Cast<ABuildingActor>(Target)) {
			if (Building->GetDisabled()) {
				NPC->SetTarget(nullptr);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		NPC->Attack();
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

bool UAI_AttackTarget::LastAttackHasFinnished(ACharacterActor* NPC) {
	return !NPC->GetMesh()->GetAnimInstance()->Montage_IsPlaying(NPC->AttackMontage);
}