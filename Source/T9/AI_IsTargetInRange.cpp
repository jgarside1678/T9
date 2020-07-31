// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_IsTargetInRange.h"
#include "CharacterActor.h"
#include "AI_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoard_Keys.h"
#include "BuildingActor.h"
#include "DrawDebugHelpers.h"

UAI_IsTargetInRange::UAI_IsTargetInRange(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Is Target In Range");
}

EBTNodeResult::Type UAI_IsTargetInRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAI_Controller* Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	ACharacterActor* const NPC = Cast<ACharacterActor>(Cont->GetPawn());
	FVector const Origin = NPC->GetActorLocation();
	UObject* Target = Cont->GetBlackboard()->GetValueAsObject(bb_keys::target_actor);

	if (Target != nullptr && Target->IsValidLowLevel()) {
		FVector TargetBounds, TargetOrigin;
		AActor* TargetActor = (AActor*)Target;
		if (ABuildingActor* Building = Cast<ABuildingActor>(TargetActor)) {
			TargetBounds = Building->BuildingExtent;
			TargetOrigin = Building->GetActorLocation();
		}
		else TargetActor->GetActorBounds(false, TargetOrigin, TargetBounds, false);
		//DrawDebugBox(GetWorld(), TargetOrigin, TargetBounds + NPC->GetAttackRange() + NPC->CapsuleRadius*2, FQuat(0, 0, 0, 0), FColor::Red, true, -1, 0, 10);
		if (UKismetMathLibrary::IsPointInBox(Origin, TargetOrigin, TargetBounds + NPC->GetAttackRange() + NPC->CapsuleRadius*2)) {
			Cont->GetBlackboard()->SetValueAsBool(bb_keys::target_is_in_range, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
		else  Cont->GetBlackboard()->SetValueAsBool(bb_keys::target_is_in_range, false);
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
