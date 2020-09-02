// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "Alliance_ResourceGatherer.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FGathererLevels {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GatherAmount = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxResourceInventory = 50;

};



UCLASS()
class T9_API AAlliance_ResourceGatherer : public AAllianceCharacter
{
	GENERATED_BODY()

public:

	AAlliance_ResourceGatherer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		TEnumAsByte<Resources> ResourceGatherType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		int GatheredResource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		bool IsGathering = false;

	UFUNCTION(BlueprintCallable, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		virtual void GatherResources();

	UFUNCTION(BlueprintCallable, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		virtual void DepositResources();

	UFUNCTION(BlueprintCallable, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		virtual bool CheckFullInventory();

	UFUNCTION(BlueprintCallable, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		int GetGatherAmount();

	UFUNCTION(BlueprintCallable, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		int GetMaxResourceInventory();


	UFUNCTION(BlueprintCallable, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		FGathererLevels GetGathererBaseStats();

	UFUNCTION(BlueprintCallable, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		FGathererLevels GetGathererUpgradeStats();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		TMap<int32, FGathererLevels> GatheringLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		int GatherAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		int MaxResourceInventory;
};
