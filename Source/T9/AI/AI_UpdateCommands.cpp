// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_UpdateCommands.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "T9/MainPlayerController.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/BlackBoard_Keys.h"


UAI_UpdateCommands::UAI_UpdateCommands(FObjectInitializer const& ObjectInitializer) {
	bNotifyBecomeRelevant = true;
	UE_LOG(LogTemp, Warning, TEXT("Constructed"));

}

void UAI_UpdateCommands::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Relevant"));
	Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	NPC = Cast<AAllianceCharacter>(Cont->GetPawn());

}


void UAI_UpdateCommands::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	if (Cont && NPC) {

		Cont->GetBlackboard()->SetValueAsVector(bb_keys::command_location, NPC->GetCommandLocation());
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

