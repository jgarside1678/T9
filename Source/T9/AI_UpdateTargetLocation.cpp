// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_UpdateTargetLocation.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "Alliance_ResourceGatherer.h"
#include "ResourceActor.h"
#include "MainPlayerController.h"
#include "MainPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "BlackBoard_Keys.h"


void UAI_UpdateTargetLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<AAlliance_ResourceGatherer>(Cont->GetPawn());
	AActor* Target = Cast<AActor>(Cont->GetBlackboard()->GetValueAsObject(bb_keys::target_actor));
	Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, Target->GetActorLocation());
}

