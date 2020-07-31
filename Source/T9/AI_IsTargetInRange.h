// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UObject/UObjectGlobals.h"
#include "CoreMinimal.h"
#include "BuildingActor.h"
#include "MainPlayerController.h"
#include "MainPlayerState.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_IsTargetInRange.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_IsTargetInRange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UAI_IsTargetInRange(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float AttackRange;
};
