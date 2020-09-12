// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_SetTargetAsHunt.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_SetTargetAsHunt : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UAI_SetTargetAsHunt(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
