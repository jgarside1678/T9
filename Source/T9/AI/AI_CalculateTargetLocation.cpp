// Copyright T9 2020


#include "AI_CalculateTargetLocation.h"
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

UAI_CalculateTargetLocation::UAI_CalculateTargetLocation(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Calculate Target Location");
}


EBTNodeResult::Type UAI_CalculateTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto NPC = Cast<ACharacterActor>(Cont->GetPawn());

	AActor* Target = NPC->Target;
	ABuildingActor* TargetBuilding = Cast<ABuildingActor>(Target);
	ACharacterActor* TargetCharacter = Cast<ACharacterActor>(Target);
	AResourceCharacter* TargetResourceCharacter = Cast<AResourceCharacter>(Target);

	if (TargetBuilding) {
		FVector ClosestBuildingBounds, ClosestBuildingOrigin;
		ClosestBuildingBounds = TargetBuilding->BuildingExtent;
		ClosestBuildingOrigin = TargetBuilding->GetActorLocation();
		FVector Direction = (NPC->GetActorLocation() - ClosestBuildingOrigin).GetSafeNormal();
		FVector TargetLocation = ClosestBuildingOrigin;
		FVector Min = FVector(ClosestBuildingOrigin.X - ClosestBuildingBounds.X - 20 - NPC->GetAttackRange(), ClosestBuildingOrigin.Y - ClosestBuildingBounds.Y - 20 - NPC->GetAttackRange(), 1);
		FVector Max = FVector(ClosestBuildingOrigin.X + ClosestBuildingBounds.X + 20 + NPC->GetAttackRange(), ClosestBuildingOrigin.Y + ClosestBuildingBounds.Y + 20 + NPC->GetAttackRange(), 1);
		FVector ClampedVector = UKismetMathLibrary::Vector_BoundedToBox(NPC->GetActorLocation(), Min, Max);
		Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, ClampedVector);
	}
	else if (TargetCharacter) {
		FVector Min = FVector(TargetCharacter->GetActorLocation() - TargetCharacter->CapsuleRadius - 10);
		FVector Max = FVector(TargetCharacter->GetActorLocation() + TargetCharacter->CapsuleRadius + 10);
		FVector ClampedVector = UKismetMathLibrary::Vector_BoundedToBox(NPC->GetActorLocation(), Min - NPC->GetAttackRange(), Max + NPC->GetAttackRange());
		Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, ClampedVector);
	}
	else if (TargetResourceCharacter) {
		FVector Min = FVector(TargetResourceCharacter->GetActorLocation() - TargetResourceCharacter->CapsuleRadius - 10);
		FVector Max = FVector(TargetResourceCharacter->GetActorLocation() + TargetResourceCharacter->CapsuleRadius + 10);
		FVector ClampedVector = UKismetMathLibrary::Vector_BoundedToBox(NPC->GetActorLocation(), Min - NPC->GetAttackRange(), Max + NPC->GetAttackRange());
		Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, ClampedVector);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
