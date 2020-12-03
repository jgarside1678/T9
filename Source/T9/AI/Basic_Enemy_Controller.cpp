// Fill out your copyright notice in the Description page of Project Settings.


#include "Basic_Enemy_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ABasic_Enemy_Controller::ABasic_Enemy_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/AI/Enemies/BasicEnemy_BT.BasicEnemy_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void ABasic_Enemy_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void ABasic_Enemy_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}
