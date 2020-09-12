// Fill out your copyright notice in the Description page of Project Settings.


#include "Alliance_Hunter_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AAlliance_Hunter_Controller::AAlliance_Hunter_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/AI/Alliance/AllianceGatherer/Alliance_Hunting_BT.Alliance_Hunting_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void AAlliance_Hunter_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AAlliance_Hunter_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}

