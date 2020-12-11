// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_UpdateTargetLocation.h"
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


UAI_UpdateTargetLocation::UAI_UpdateTargetLocation(FObjectInitializer const& ObjectInitializer) {
	bNotifyBecomeRelevant = true;
	UE_LOG(LogTemp, Warning, TEXT("Constructed"));

}

void UAI_UpdateTargetLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Relevant"));
	Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	NPC = Cast<ACharacterActor>(Cont->GetPawn());

	Target = Cast<AActor>(Cont->GetBlackboard()->GetValueAsObject(bb_keys::combat_target));
	TargetBuilding = Cast<ABuildingActor>(Target);
	TargetCharacter = Cast<ACharacterActor>(Target);
	TargetResourceCharacter = Cast<AResourceCharacter>(Target);
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}


void UAI_UpdateTargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	if (TargetBuilding) {
		FVector ClosestBuildingBounds, ClosestBuildingOrigin;
		ClosestBuildingBounds = TargetBuilding->BuildingExtent;
		ClosestBuildingOrigin = TargetBuilding->GetActorLocation();
		FVector Direction = (NPC->GetActorLocation() - ClosestBuildingOrigin).GetSafeNormal();
		FVector TargetLocation = ClosestBuildingOrigin;
		FVector Min = FVector(ClosestBuildingOrigin.X - ClosestBuildingBounds.X - 20 - NPC->GetAttackRange(), ClosestBuildingOrigin.Y - ClosestBuildingBounds.Y - 20 - NPC->GetAttackRange(), 1);
		FVector Max = FVector(ClosestBuildingOrigin.X + ClosestBuildingBounds.X + 20 + NPC->GetAttackRange(), ClosestBuildingOrigin.Y + ClosestBuildingBounds.Y + 20 + NPC->GetAttackRange(), 1);
		FVector ClampedVector = UKismetMathLibrary::Vector_BoundedToBox(NPC->GetActorLocation(), Min, Max);
		DrawDebugLine(GetWorld(), ClampedVector, FVector(ClampedVector.X, ClampedVector.Y, 2000), FColor::Green, false, 10, 0, 10);
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
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

