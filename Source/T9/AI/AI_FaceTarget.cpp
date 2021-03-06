// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FaceTarget.h"
#include "AI_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/Characters/CharacterActor.h"
#include "T9/BlackBoard_Keys.h"

UAI_FaceTarget::UAI_FaceTarget(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Face Target");
}

EBTNodeResult::Type UAI_FaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<ACharacterActor>(Cont->GetPawn());

	FVector const Origin = NPC->GetActorLocation();
	UObject* Target = Cont->GetBlackboard()->GetValueAsObject(BlackboardKey.SelectedKeyName);

	if (Target != nullptr && Target->IsValidLowLevel()) {
		AActor* TargetActor = (AActor*)Target;
		FVector TargetOrigin = TargetActor->GetActorLocation();
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Origin, TargetOrigin);
		NPC->SetActorRotation(FRotator(0, Rotation.Yaw, 0));
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}