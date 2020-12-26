// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_IsTargetInRange.h"
#include "AI_Controller.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "DrawDebugHelpers.h"

UAI_IsTargetInRange::UAI_IsTargetInRange(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Is Target In Range");
}

EBTNodeResult::Type UAI_IsTargetInRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAI_Controller* Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	ACharacterActor* const NPC = Cast<ACharacterActor>(Cont->GetPawn());
	FVector const Origin = NPC->GetActorLocation();
	AActor* Target = NPC->Target;
	float AttackRange = NPC->GetAttackRange() + NPC->GetCapsuleComponent()->GetScaledCapsuleRadius() + 100;

	if (Target != nullptr && Target->IsValidLowLevel()) {
		FVector TargetBounds, TargetOrigin;
		if (ABuildingActor* Building = Cast<ABuildingActor>(Target)) {
			TargetBounds = Building->BuildingExtent;
			TargetOrigin = Building->GetActorLocation();
		}
		else Target->GetActorBounds(false, TargetOrigin, TargetBounds, false);

		TargetBounds = FVector(TargetBounds + AttackRange);

		if (UKismetMathLibrary::IsPointInBox(Origin, TargetOrigin, TargetBounds)) {
			Cont->GetBlackboard()->SetValueAsBool(bb_keys::target_is_in_range, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
		else  Cont->GetBlackboard()->ClearValue(bb_keys::target_is_in_range);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
