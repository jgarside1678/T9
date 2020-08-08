// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "Alliance_ResourceGatherer.generated.h"

/**
 * 
 */


USTRUCT()
struct FGathererUpgrades {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int GatherAmount = 50;

	UPROPERTY(EditAnywhere)
		float MaxResourceInventory = 50;

	UPROPERTY(EditAnywhere)
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere)
		float Damage = 10;

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

protected:

	UPROPERTY(VisibleAnywhere, Category = "Gathering", Meta = (AllowPrivateAccess = "true"))
		TMap<int32, FGathererUpgrades> Upgrades;
};
