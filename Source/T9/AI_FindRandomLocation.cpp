// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FindRandomLocation.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "CharacterActor.h"
#include "BuildingActor.h"
#include "BlackBoard_Keys.h"
#include "DrawDebugHelpers.h"


UAI_FindRandomLocation::UAI_FindRandomLocation(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UAI_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cont->GetPawn();
	FVector const Origin = NPC->GetActorLocation();

	ACharacterActor* Character = (ACharacterActor*)NPC;
	ABuildingActor* SpawnBuilding = nullptr;
	FVector SpawnBoxExtent, SpawnOrigin;
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation RadiusLocation;
	FVector RectLocation;

	if (Character) {
		SpawnBuilding = Cast<ABuildingActor>(Character->GetSpawnBuilding());
		if (SpawnBuilding != nullptr) {
			SpawnBuilding->GetBuildingRangeCollider(SpawnOrigin, SpawnBoxExtent);
		}
	}

	if (SpawnBuilding) {
		RectLocation = UKismetMathLibrary::RandomPointInBoundingBox((SpawnOrigin), (SpawnBoxExtent));
		Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, RectLocation);
		//DrawDebugBox(GetWorld(), (SpawnOrigin), (SpawnBoxExtent), FColor::Blue, true, -1, 0, 10);
	}
	else {
		if (!StayNearSpawnLocation) {
			if (NavSystem->GetRandomPointInNavigableRadius(Origin, MaxWalkDistance, RadiusLocation, nullptr)) {
				Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, RadiusLocation.Location);
			}
		}
		else {
			if (NavSystem->GetRandomPointInNavigableRadius(Character->InitalLocation, MaxWalkDistance, RadiusLocation, nullptr)) {
				Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, RadiusLocation.Location);
			}
		}
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}
