// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/ResourceBuildingActor.h"
#include "Building_Windmill.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ABuilding_Windmill : public AResourceBuildingActor
{
	GENERATED_BODY()
public:

	ABuilding_Windmill(const FObjectInitializer& ObjectInitializer);


	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	class UBuildingSpawnComponent* SpawnComponent;


protected:

	virtual void BeginPlay() override;

	virtual void Upgrade() override;

	virtual void ResourceInit() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* AdditionalStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class URotatingMovementComponent* RotationComp;

};
