// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI_GatherResources.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_GatherResources : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_GatherResources(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
