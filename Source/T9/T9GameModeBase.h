// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "T9GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class T9_API AT9GameModeBase : public AGameModeBase
{

	GENERATED_BODY()
public:
	AT9GameModeBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY()
		TArray<AActor*> FoundActors;
public:

	UPROPERTY()
		class AGameGridActor* Grid;


};
