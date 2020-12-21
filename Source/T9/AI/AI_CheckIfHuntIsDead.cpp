// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_CheckIfHuntIsDead.h"
#include "AI_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/Interfaces/DamageInterface.h"
#include "T9/BlackBoard_Keys.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "DrawDebugHelpers.h"

UAI_CheckIfHuntIsDead::UAI_CheckIfHuntIsDead(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Is Hunt Dead");
}

EBTNodeResult::Type UAI_CheckIfHuntIsDead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAI_Controller* Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	ACharacterActor* const NPC = Cast<ACharacterActor>(Cont->GetPawn());
	UObject* HuntTarget = Cont->GetBlackboard()->GetValueAsObject(bb_keys::hunt);

	if (HuntTarget != nullptr && HuntTarget->IsValidLowLevel()) {
		IDamageInterface* Enemy = Cast<IDamageInterface>(HuntTarget);
		if (Enemy != nullptr) {
			bool Dead = Enemy->CheckIfDead();
			Cont->GetBlackboard()->SetValueAsBool(bb_keys::target_is_dead, Dead);
			if (Dead) Cont->GetBlackboard()->SetValueAsObject(bb_keys::utility_target, HuntTarget);
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}