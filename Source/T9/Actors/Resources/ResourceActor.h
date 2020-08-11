// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T9/Interfaces/SelectInterface.h"
#include "ResourceActor.generated.h"


UENUM()
enum Resources
{
	Wood UMETA(DisplayName = "Wood"),
	Stone UMETA(DisplayName = "Stone"),
	Food UMETA(DisplayName = "Food")
};


UCLASS()
class T9_API AResourceActor : public AActor, public ISelectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gathering")
		TEnumAsByte<Resources> ResourceType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource Static Meshs", Meta = (AllowPrivateAccess = "true"))
		class UInstancedStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource Box Collider", Meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class AMainPlayerState* PS;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		FString Name = "Resource";

	UPROPERTY()
	    TArray<UStaticMeshComponent*> Meshs;

	UPROPERTY()
		int OutlineColour = 1;

	UPROPERTY()
		FVector BoxExtentMultiplier = FVector(1);


public:	
	// Called every frame
	UPROPERTY()
		FVector CollectionDistance = FVector(100);

	virtual void Tick(float DeltaTime) override;

	void GetClosestStaticMesh(FVector Location, FVector& ClosestMeshLocation, FVector& ClosestMeshBounds);

	UFUNCTION()
		virtual void SetSelected() override;

	UFUNCTION()
		virtual void SetUnSelected() override;

	UFUNCTION(BlueprintCallable)
		virtual FString GetName() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GridSpace;

	UFUNCTION()
		void ResourceInit(class AGameGridActor* Grid);

};
