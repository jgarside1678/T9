// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FindClosestResource.h"
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

UAI_FindClosestResource::UAI_FindClosestResource(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Find Closest Resource");
}

EBTNodeResult::Type UAI_FindClosestResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AResourceActor* ClosestResource = nullptr;
	float CRDistanceToActor, DistanceToActor;
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<AAlliance_ResourceGatherer>(Cont->GetPawn());

	//Clear Last Target incase animations still playing
	NPC->CurrentTarget = nullptr;
	if (!NPC->IsDead) {
		AResourceActor* Target = Cast<AResourceActor>(Cont->GetBlackboard()->GetValueAsObject(bb_keys::target_actor));
		FVector const Origin = NPC->GetActorLocation();

		//Locate nearest Building
		SpawnedResources = PS->SpawnedResources;
		for (int x = 0; x < SpawnedResources.Num(); x++) {
			if (SpawnedResources[x]->ResourceType == NPC->ResourceGatherType) {
				if ((SpawnedResources[x] != nullptr) && (!SpawnedResources[x]->IsPendingKill())) {
					DistanceToActor = (Origin - SpawnedResources[x]->GetActorLocation()).Size();
					if (ClosestResource == nullptr) {
						ClosestResource = SpawnedResources[x];
						CRDistanceToActor = DistanceToActor;
					}
					else if (DistanceToActor < CRDistanceToActor) {
						ClosestResource = SpawnedResources[x];
						CRDistanceToActor = DistanceToActor;
					}
				}
			}
		}

		if ((ClosestResource != nullptr) && (Target != ClosestResource)) {
			FVector ClosestResourceBounds, ClosestResourceOrigin;
			ClosestResource->GetClosestStaticMesh(Origin, ClosestResourceOrigin, ClosestResourceBounds);
			FVector Direction = (Origin - ClosestResourceOrigin).GetSafeNormal();
			FVector Min = FVector(ClosestResourceOrigin.X - ClosestResourceBounds.X, ClosestResourceOrigin.Y - ClosestResourceBounds.Y, 0.f);
			FVector Max = FVector(ClosestResourceOrigin.X + ClosestResourceBounds.X, ClosestResourceOrigin.Y + ClosestResourceBounds.Y, 0.f);
			FVector ClampedVector = UKismetMathLibrary::Vector_BoundedToBox(Origin, Min - NPC->CapsuleRadius, Max + NPC->CapsuleRadius);

			Cont->GetBlackboard()->SetValueAsObject(bb_keys::target_actor, (UObject*)ClosestResource);
			Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, ClampedVector);

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}

	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;

}
