// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "AI_IsTargetInRangeService.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_IsTargetInRangeService : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_IsTargetInRangeService(FObjectInitializer const& ObjectInitializer);

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	UPROPERTY()
		class AAI_Controller* Cont;

	UPROPERTY()
		class ACharacterActor* NPC;
};
