// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainActor.generated.h"

UCLASS()
class T9_API ATerrainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CollisionEnabled = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain Basics", Meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* TerrainCollider;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
