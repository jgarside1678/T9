// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_FaceTarget.h"
#include "AI_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "CharacterActor.h"
#include "BlackBoard_Keys.h"

UAI_FaceTarget::UAI_FaceTarget(FObjectInitializer const& ObjectInitializer) {
	NodeName = TEXT("Face Target");
}

EBTNodeResult::Type UAI_FaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Cont = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	auto const NPC = Cast<ACharacterActor>(Cont->GetPawn());
	FVector const Origin = NPC->GetActorLocation();
	UObject* Target = Cont->GetBlackboard()->GetValueAsObject(bb_keys::target_actor);

	if (Target != nullptr && Target->IsValidLowLevel()) {
		FVector TargetBounds, TargetOrigin;
		AActor* TargetActor = (AActor*)Target;
		TargetActor->GetActorBounds(false, TargetOrigin, TargetBounds, false);
		FVector Forward = TargetOrigin - Origin;
		FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, FVector(0, 0, 0));
		NPC->SetActorRotation(FRotator(0, Rot.Yaw, 0));
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}