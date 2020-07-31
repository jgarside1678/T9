// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_DepositResources.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_DepositResources : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_DepositResources(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
