// Copyright T9 2020


#include "AI_IsTargetInRangeService.h"

#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "T9/MainPlayerController.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/MainPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "T9/BlackBoard_Keys.h"


UAI_IsTargetInRangeService::UAI_IsTargetInRangeService(FObjectInitializer const& ObjectInitializer) {
	bNotifyBecomeRelevant = true;

}

void UAI_IsTargetInRangeService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	NPC = Cast<ACharacterActor>(Cont->GetPawn());
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}


void UAI_IsTargetInRangeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

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
		DrawDebugBox(GetWorld(), TargetOrigin, TargetBounds, FColor::Green, false, 10, 0, 10);
		if (UKismetMathLibrary::IsPointInBox(Origin, TargetOrigin, TargetBounds)) {
			Cont->GetBlackboard()->SetValueAsBool(bb_keys::target_is_in_range, true);
		}
		else  Cont->GetBlackboard()->ClearValue(bb_keys::target_is_in_range);
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}