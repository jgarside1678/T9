// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Bear_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AResource_Bear_Controller::AResource_Bear_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/AI/Neutral/Neutral_Bear_BT.Neutral_Bear_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void AResource_Bear_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AResource_Bear_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}
