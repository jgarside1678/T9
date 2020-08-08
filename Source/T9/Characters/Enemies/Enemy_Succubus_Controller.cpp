// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Succubus_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemy_Succubus_Controller::AEnemy_Succubus_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/AI/ModularCharacterSuccubus/Succubus_BT.Succubus_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void AEnemy_Succubus_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Succubus_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}
