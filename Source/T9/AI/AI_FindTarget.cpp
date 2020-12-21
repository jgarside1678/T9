// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FindTarget.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Actors/GameGridActor.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"
#include "Kismet/KismetMathLibrary.h"
#include "T9/T9GameModeBase.h"
#include "Math/Vector.h"

UAI_FindTarget::UAI_FindTarget(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Find Target");
}


EBTNodeResult::Type UAI_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	AActor* ClosestActor = nullptr;
	float CBDistanceToActor, DistanceToActor;
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<ACharacterActor>(Cont->GetPawn());

	//Clear Last Target incase animations still playing
	NPC->Target = nullptr;
	if (!NPC->IsDead) {
		AActor* Target = Cast<AActor>(Cont->GetBlackboard()->GetValueAsObject(bb_keys::combat_target));
		FVector const Origin = NPC->GetActorLocation();
		if (Target == nullptr || Target->IsPendingKill()) {
			//Locate nearest Building
			if (NPC->TargetBuildings) {
				BuiltBuildings = PS->SpawnedBuildings;
				for (int x = 0; x < BuiltBuildings.Num(); x++) {
					if ((BuiltBuildings[x] != nullptr) && (!BuiltBuildings[x]->IsPendingKill()) && !BuiltBuildings[x]->GetDisabled()) {
						DistanceToActor = (Origin - BuiltBuildings[x]->GetActorLocation()).Size();
						if (NPC->AwarenessDistance != 0 && NPC->AwarenessDistance < DistanceToActor) continue;
						if (ClosestActor == nullptr) {
							ClosestActor = BuiltBuildings[x];
							CurrentType = Building;
							CBDistanceToActor = DistanceToActor;
						}
						else if (DistanceToActor < CBDistanceToActor) {
							ClosestActor = BuiltBuildings[x];
							CurrentType = Building;
							CBDistanceToActor = DistanceToActor;
						}
					}
				}
			}

			//Locate nearest Character
			if (NPC->TargetCharacters) {
				if (Cast<AEnemyCharacter>(NPC)) {
					SpawnedAlliance = PS->SpawnedAllianceCharacters;
					for (int x = 0; x < SpawnedAlliance.Num(); x++) {
						if ((SpawnedAlliance[x] != nullptr) && (!SpawnedAlliance[x]->IsPendingKill()) && (!SpawnedAlliance[x]->CheckInvulnerable())) {
							DistanceToActor = (Origin - SpawnedAlliance[x]->GetActorLocation()).Size();
							if (NPC->AwarenessDistance != 0 && NPC->AwarenessDistance < DistanceToActor) continue;
							if (ClosestActor == nullptr) {
								ClosestActor = SpawnedAlliance[x];
								CurrentType = Character;
								CBDistanceToActor = DistanceToActor;
							}
							else if (DistanceToActor < CBDistanceToActor) {
								ClosestActor = SpawnedAlliance[x];
								CurrentType = Character;
								CBDistanceToActor = DistanceToActor;
							}
						}
					}
				}
				else if (Cast<AAllianceCharacter>(NPC)) {
					SpawnedEnemies = PS->SpawnedEnemyCharacters;
					for (int x = 0; x < SpawnedEnemies.Num(); x++) {
						if ((SpawnedEnemies[x] != nullptr) && (!SpawnedEnemies[x]->IsPendingKill()) && (!SpawnedEnemies[x]->CheckInvulnerable())) {
							DistanceToActor = (Origin - SpawnedEnemies[x]->GetActorLocation()).Size();
							if (NPC->AwarenessDistance != 0 && NPC->AwarenessDistance < DistanceToActor) continue;
							if (ClosestActor == nullptr) {
								ClosestActor = SpawnedEnemies[x];
								CurrentType = Character;
								CBDistanceToActor = DistanceToActor;
							}
							else if (DistanceToActor < CBDistanceToActor) {
								ClosestActor = SpawnedEnemies[x];
								CurrentType = Character;
								CBDistanceToActor = DistanceToActor;
							}
						}
					}
				}
			}
		}
		else ClosestActor = Target;
		NPC->SetTarget(ClosestActor);

	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
