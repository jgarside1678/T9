// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "Building_Wall.generated.h"

UENUM()
enum class WallState
{
	Node UMETA(DisplayName = "Node"),
	Connection UMETA(DisplayName = "Connection")
};


UCLASS()
class T9_API ABuilding_Wall : public ABuildingActor
{
	GENERATED_BODY()

public:

	ABuilding_Wall();

	virtual void BuildingInit(AGameGridActor* BuildingGrid, FVector PivotLocation, FVector CornerLocation, int Rotation) override;

	UFUNCTION()
		int GetCurrentState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall State")
		WallState CurrentState = WallState::Node;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Basics")
		UStaticMesh* Node;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Basics")
		UStaticMesh* Connection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Basics")
		ABuilding_Wall* Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Basics")
		ABuilding_Wall* Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Basics")
		ABuilding_Wall* Top;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Basics")
		ABuilding_Wall* Bottom;

	UFUNCTION()
		void SetupWall();

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult) override;

	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex) override;

};
