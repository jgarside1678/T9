// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UObject/UObjectGlobals.h"
#include "CoreMinimal.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_FindTarget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class T9_API UAI_FindTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UAI_FindTarget(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	//virtual void InitializeFromAsset(UBehaviorTree& Asset) override;


private:

	enum TargetType { Building, Character };

	TargetType CurrentType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		TArray<ABuildingActor*> BuiltBuildings;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		TArray<ACharacterActor*> SpawnedEnemies;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		TArray<ACharacterActor*> SpawnedAlliance;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		class AT9GameModeBase* GameMode;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
		class AGameGridActor* Grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;
};
