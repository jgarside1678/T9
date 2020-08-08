// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_UpdateTargetLocation.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Characters/Alliance/Alliance_ResourceGatherer.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "T9/BlackBoard_Keys.h"


void UAI_UpdateTargetLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<AAlliance_ResourceGatherer>(Cont->GetPawn());
	AActor* Target = Cast<AActor>(Cont->GetBlackboard()->GetValueAsObject(bb_keys::target_actor));
	Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, Target->GetActorLocation());
}

