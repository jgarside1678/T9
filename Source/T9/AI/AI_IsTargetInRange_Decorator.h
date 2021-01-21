// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "AI_IsTargetInRange_Decorator.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_IsTargetInRange_Decorator : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:

	UAI_IsTargetInRange_Decorator(FObjectInitializer const& ObjectInitializer);

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


	//virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;



protected:

	//UPROPERTY()
	//	class AAI_Controller* Controller;

	//UPROPERTY()
	//	class ACharacterActor* NPC;

	UPROPERTY()
		class UBlackboardComponent* BlackboardComp;
};
