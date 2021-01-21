// Copyright T9 2020


#include "T9/AI/AI_IsTargetInRange_Decorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "AI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/Actors/Buildings/BuildingActor.h"

UAI_IsTargetInRange_Decorator::UAI_IsTargetInRange_Decorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Is Target In Range";
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}




bool UAI_IsTargetInRange_Decorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAI_Controller* Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	ACharacterActor* NPC = Cast<ACharacterActor>(Controller->GetPawn());
	if (NPC) {
		FVector const Origin = NPC->GetActorLocation();
		AActor* Target = NPC->Target;
		float AttackRange = NPC->GetAttackRange() + NPC->CapsuleRadius + 50;
		if (Target != nullptr && Target->IsValidLowLevel()) {
			FVector TargetBounds, TargetOrigin;
			if (ABuildingActor* Building = Cast<ABuildingActor>(Target)) {
				TargetBounds = Building->BuildingExtent;
				TargetOrigin = Building->GetActorLocation();
			}
			else Target->GetActorBounds(false, TargetOrigin, TargetBounds, false);

			TargetBounds = FVector(TargetBounds + AttackRange);
			if (UKismetMathLibrary::IsPointInBox(Origin, TargetOrigin, TargetBounds)) {
				return true;
			}
		}
	}
	return false;
}


void UAI_IsTargetInRange_Decorator::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UAI_IsTargetInRange_Decorator::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->UnregisterObserversFrom(this);
	}
}
