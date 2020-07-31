// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "AI_UpdateTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_UpdateTargetLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//UAI_UpdateTargetLocation(FObjectInitializer const& ObjectInitializer);
};
