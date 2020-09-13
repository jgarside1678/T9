// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "Resource_Food.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AResource_Food : public AResourceActor
{
	GENERATED_BODY()
public:
	AResource_Food();

protected:

	virtual void ResourceInit(class AGameGridActor* Grid, TEnumAsByte<Tiers> StartingResourceTier = Tier1) override;


private:
};
