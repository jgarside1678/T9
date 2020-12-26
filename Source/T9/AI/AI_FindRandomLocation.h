// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "BehaviorTree/BahaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "AI_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class T9_API UAI_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_FindRandomLocation(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Search", Meta = (AllowPrivateAccess = "true"))
		//Only Uses this for NPCs not assigned to a spawn building.
		float MaxWalkDistance = 100.0f;

};
