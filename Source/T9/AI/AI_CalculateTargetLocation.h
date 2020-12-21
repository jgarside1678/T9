// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_CalculateTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_CalculateTargetLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_CalculateTargetLocation(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
