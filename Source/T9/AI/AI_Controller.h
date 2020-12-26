// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
public:
	AAI_Controller(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	void BeginPlay() override;

	void OnPossess(APawn* const pawn) override;

	class UBlackboardComponent* GetBlackboard() const;

	class UCrowdFollowingComponent* GetCrowdManager() const;

protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", Meta = (AllowPrivateAccess = "true"))
		class UCrowdFollowingComponent* CrowdManager;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", Meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", Meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BTree;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", Meta = (AllowPrivateAccess = "true"))
		class UBlackboardComponent* NPCBlackboard;
};
