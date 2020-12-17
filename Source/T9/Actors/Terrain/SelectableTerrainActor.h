// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T9/Actors/Terrain/TerrainActor.h"
#include "T9/Interfaces/SelectInterface.h"
#include "SelectableTerrainActor.generated.h"

UCLASS()
class T9_API ASelectableTerrainActor : public ATerrainActor, public ISelectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectableTerrainActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain Basics")
		FString TerrainName = "Terrain";


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void SetSelected() override;

	UFUNCTION()
		virtual void SetUnSelected() override;

	UFUNCTION(BlueprintCallable)
		virtual FString GetName() override;

	UFUNCTION(BlueprintCallable)
		virtual int GetLevel() override;

};
