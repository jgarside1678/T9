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
		AResourceActor* Target = Cast<AResourceActor>(Cont->GetBlackboard()->GetValueAsObject(bb_keys::target_actor));
		FVector const Origin = NPC->GetActorLocation();

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
			ClosestResource->GetClosestSpawnedCharacter(Origin, TargetCharacter);
			if (TargetCharacter) {
				UE_LOG(LogTemp, Warning, TEXT("Wagwan"));
				float ClosestResourceCharacterBounds = TargetCharacter->CapsuleRadius;
				FVector ClosestResourceCharacterOrigin = TargetCharacter->GetActorLocation();
				FVector Direction = (Origin - ClosestResourceCharacterOrigin).GetSafeNormal();
				FVector Min = FVector(ClosestResourceCharacterOrigin.X - ClosestResourceCharacterBounds, ClosestResourceCharacterOrigin.Y - ClosestResourceCharacterBounds, 1);
				FVector Max = FVector(ClosestResourceCharacterOrigin.X + ClosestResourceCharacterBounds, ClosestResourceCharacterOrigin.Y + ClosestResourceCharacterBounds, 1);
				FVector ClampedVector = UKismetMathLibrary::Vector_BoundedToBox(Origin, Min - NPC->CapsuleRadius - NPC->GetAttackRange(), Max + NPC->CapsuleRadius + NPC->GetAttackRange());
				DrawDebugLine(GetWorld(), ClampedVector, FVector(ClampedVector.X, ClampedVector.Y, 3000), FColor::Blue, false, 20, 0, 10);
				Cont->GetBlackboard()->SetValueAsObject(bb_keys::target_actor, (UObject*)TargetCharacter);
				Cont->GetBlackboard()->SetValueAsBool(bb_keys::target_is_dead, false);
				Cont->GetBlackboard()->SetValueAsObject(bb_keys::hunt, (UObject*)TargetCharacter);
				Cont->GetBlackboard()->SetValueAsObject(bb_keys::resource, (UObject*)ClosestResource);
				Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, ClampedVector);
			}
		}

	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

