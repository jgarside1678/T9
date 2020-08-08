// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FindSpawnBuilding.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

UAI_FindSpawnBuilding::UAI_FindSpawnBuilding(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Find Spawn Building");
}

EBTNodeResult::Type UAI_FindSpawnBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABuildingActor* SpawnBuilding = nullptr;
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<ACharacterActor>(Cont->GetPawn());

	if (NPC && !NPC->IsDead) {
		FVector const Origin = NPC->GetActorLocation();
		SpawnBuilding = Cast<ABuildingActor>(NPC->GetSpawnBuilding());
		if (SpawnBuilding != nullptr) {
			Cont->GetBlackboard()->SetValueAsVector(bb_keys::move_location, SpawnBuilding->GetActorLocation());
			Cont->GetBlackboard()->SetValueAsObject(bb_keys::target_actor, (UObject*)SpawnBuilding);
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;

}

