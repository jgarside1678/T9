// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Goat_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AResource_Goat_Controller::AResource_Goat_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/AI/Neutral/Neutral_Goat_BT.Neutral_Goat_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void AResource_Goat_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AResource_Goat_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}
