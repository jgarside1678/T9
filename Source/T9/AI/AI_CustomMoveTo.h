// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "AI_CustomMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_CustomMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:

	UAI_CustomMoveTo(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);


};
