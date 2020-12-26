// Fill out your copyright notice in the Description page of Project Settings.
#include "AI_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAI_Controller::AAI_Controller(FObjectInitializer const& object_initializer) : Super(object_initializer.SetDefaultSubobjectClass(TEXT("PathFollowingComponent"), UCrowdFollowingComponent::StaticClass()))
{
	BTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaveComp"));
	NPCBlackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	CrowdManager = (UCrowdFollowingComponent*)GetPathFollowingComponent();
	CrowdManager->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
	CrowdManager->SetCrowdRotateToVelocity(false);
	CrowdManager->SetCrowdAnticipateTurns(false);
	CrowdManager->SetCrowdSlowdownAtGoal(false);
}

void AAI_Controller::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BTree);
	BTreeComponent->StartTree(*BTree);
}

void AAI_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (NPCBlackboard) {
		NPCBlackboard->InitializeBlackboard(*BTree->BlackboardAsset);
	}
}

UBlackboardComponent* AAI_Controller::GetBlackboard() const
{
	return NPCBlackboard;
}


UCrowdFollowingComponent* AAI_Controller::GetCrowdManager() const
{
	return CrowdManager;
}