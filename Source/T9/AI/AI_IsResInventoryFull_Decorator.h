// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "AI_IsResInventoryFull_Decorator.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_IsResInventoryFull_Decorator : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_IsResInventoryFull_Decorator(FObjectInitializer const& ObjectInitializer);

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY()
		class UBlackboardComponent* BlackboardComp;
};