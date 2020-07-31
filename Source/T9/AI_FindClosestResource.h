// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_FindClosestResource.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_FindClosestResource : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UAI_FindClosestResource(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		TArray<class AResourceActor*> SpawnedResources;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;
};
