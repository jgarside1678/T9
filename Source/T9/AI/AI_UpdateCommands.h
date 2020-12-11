// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "AI_UpdateCommands.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_UpdateCommands : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_UpdateCommands(FObjectInitializer const& ObjectInitializer);

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	UPROPERTY()
		class AAI_Controller* Cont;

	UPROPERTY()
		class AAllianceCharacter* NPC;

};

