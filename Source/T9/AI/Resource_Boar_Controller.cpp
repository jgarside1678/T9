// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Boar_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AResource_Boar_Controller::AResource_Boar_Controller(FObjectInitializer const& object_initializer) {

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/AI/Neutral/Neutral_Boar_BT.Neutral_Boar_BT'"));
	if (Obj.Succeeded()) {
		BTree = Obj.Object;
	}
}

void AResource_Boar_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AResource_Boar_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}

