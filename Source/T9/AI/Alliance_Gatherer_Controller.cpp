// Fill out your copyright notice in the Description page of Project Settings.


#include "Alliance_Gatherer_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AAlliance_Gatherer_Controller::AAlliance_Gatherer_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/Units/Alliance/AllianceGatherer/Alliance_Gathering_BT.Alliance_Gathering_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void AAlliance_Gatherer_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AAlliance_Gatherer_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}
