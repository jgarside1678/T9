// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FindClosestResourceCharacter.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Characters/Alliance/Alliance_ResourceGatherer.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "T9/BlackBoard_Keys.h"

UAI_FindClosestResourceCharacter::UAI_FindClosestResourceCharacter(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Find Closest Resource Character");
}

EBTNodeResult::Type UAI_FindClosestResourceCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AResourceActor* ClosestResource = nullptr;
	float CRDistanceToActor, DistanceToActor;
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<AAlliance_ResourceGatherer>(Cont->GetPawn());

	if (!NPC->IsDead) {
		AResourceCharacter* CommandedTarget = NPC->GetCommandedResourceCharacter();
		AResourceActor* Target = Cast<AResourceActor>(Cont->GetBlackboard()->GetValueAsObject(bb_keys::utility_target));
		FVector const Origin = NPC->GetActorLocation();
		NPC->IsGathering = false;
		//Locate nearest Building
		SpawnedResources = PS->SpawnedResources;
		for (int x = 0; x < SpawnedResources.Num(); x++) {
			if (SpawnedResources[x]->ResourceType == NPC->ResourceGatherType) {
				if ((SpawnedResources[x] != nullptr) && (!SpawnedResources[x]->IsPendingKill())) {
					DistanceToActor = (Origin - SpawnedResources[x]->GetActorLocation()).Size();
					if (ClosestResource == nullptr || DistanceToActor < CRDistanceToActor) {
						ClosestResource = SpawnedResources[x];
						CRDistanceToActor = DistanceToActor;
					}
				}
			}
		}

		if ((ClosestResource != nullptr) && (Target != ClosestResource)) {
			AResourceCharacter* TargetCharacter = nullptr;
			if (CommandedTarget) ClosestResource = CommandedTarget->GetParentResource();
			NPC->SetResource(ClosestResource);
			if (CommandedTarget) TargetCharacter = CommandedTarget;
			else ClosestResource->GetClosestSpawnedCharacter(Origin, TargetCharacter);
			if (TargetCharacter) {
				NPC->SetHuntTarget(TargetCharacter);
				Cont->GetBlackboard()->SetValueAsObject(bb_keys::resource, (UObject*)ClosestResource);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}

	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

