// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FindRandomLocation.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "DrawDebugHelpers.h"



UAI_FindRandomLocation::UAI_FindRandomLocation(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UAI_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cont->GetPawn();
	FVector const Origin = NPC->GetActorLocation();
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation RadiusLocation;


	if (NavSystem->GetRandomPointInNavigableRadius(Origin, MaxWalkDistance, RadiusLocation, nullptr)) {
		Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, RadiusLocation.Location);
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}
