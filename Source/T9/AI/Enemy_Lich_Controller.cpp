// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Lich_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemy_Lich_Controller::AEnemy_Lich_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/AI/Enemies/BasicEnemy_BT.BasicEnemy_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void AEnemy_Lich_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Lich_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}
