// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_ResourceCharacter_NewLocation.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "T9/BlackBoard_Keys.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "DrawDebugHelpers.h"


UAI_ResourceCharacter_NewLocation::UAI_ResourceCharacter_NewLocation(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Find New Location");
}

EBTNodeResult::Type UAI_ResourceCharacter_NewLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cont->GetPawn();
	//FVector const Origin = NPC->GetActorLocation();

	AResourceCharacter* Character = (AResourceCharacter*)NPC;
	AResourceActor* SpawnResource = Character->GetParentResource();
	FVector SpawnBoxExtent, SpawnOrigin;
	FVector RectLocation;

	if (SpawnResource) {
		SpawnResource->GetActorBounds(true, SpawnOrigin, SpawnBoxExtent);
		RectLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnBoxExtent);
		Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, FVector(RectLocation.X, RectLocation.Y, 1));
		//DrawDebugBox(GetWorld(), (SpawnOrigin), (SpawnBoxExtent), FColor::Blue, true, -1, 0, 10);
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

