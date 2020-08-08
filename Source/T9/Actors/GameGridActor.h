// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T9/Widgets/GameHUD.h"
#include "GameGridActor.generated.h"


UCLASS()
class T9_API AGameGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsGridSlotUsed[189][189];

	UFUNCTION()
		void SetTilesActive(FVector Location, int TilesWidth, int TilesHeight);

	UFUNCTION()
		void SetTilesUnactive(FVector Location, int TilesWidth, int TilesHeight, int Rotation);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		TArray<FVector> Vertices;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		TArray<int> Triangles;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		TArray<FVector> SelectionVertices;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		TArray<int> SelectionTriangles;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		int NumberOfRows = 189;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		int NumberOfColumns = 189;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		int CurrentRow;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		int CurrentColumn;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		FVector SelectionGridPivotLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		FVector SelectedGridLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		float TileSize = 100;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid")
		float LineThickness = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		class UMaterialInstance* LineColour;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		class UMaterialInstance* SelectionColour;

	UFUNCTION(Category = "Grid")
		bool LocationToTile(const FVector &Location);

	UFUNCTION(Category = "Grid")
		bool TileToGridLocation();

	UFUNCTION()
		bool CheckGridLocation(FVector CheckLocation, int BuildingWidth, int BuildingHeight);

	UFUNCTION(Category = "Grid")
		void SetSelectedTile();

	UFUNCTION()
		class ABuildingActor* BuildBuildingOnTile(FBuildingMenu ObjectToBuild);

	UFUNCTION()
		class AWallActor* BuildWallOnTile(FBuildingMenu ObjectToBuild);

	UFUNCTION()
		void ToggleSelectionTile(bool Toggle);

	UFUNCTION()
		void ScaleSelectionTile(int ScaleX, int ScaleY);


	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	//	TArray<ABuildingActor*> BuiltBuildings;

	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	//	TArray<AWallActor*> BuiltWalls;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		class UMaterial* PreviewMaterial;

	UFUNCTION()
		AActor* CreatePreviewObject(FBuildingMenu ObjectToBuild);

	UFUNCTION()
		void MovePreviewObject(FVector Location);

	UFUNCTION()
		void RotatePreviewObject(int RotationAmount);

	UFUNCTION()
		bool DestroyPreviewObject();

	//UFUNCTION()
	//	void BuildingArrayClean();

	UFUNCTION()
		void ToggleGridSpaces(bool Input);


private:
	UPROPERTY()
		AActor* PreviewBuilding;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid", Meta = (AllowPrivateAccess = "true"))
		class UProceduralMeshComponent* LineMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid", Meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SelectionMeshRotationPivot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Grid", Meta = (AllowPrivateAccess = "true"))
		class UProceduralMeshComponent* SelectionMesh;

	UPROPERTY()
		int SelectionLengthX;

	UPROPERTY()
		int SelectionLengthY;

	UPROPERTY()
		int SelectionRotationY = 0;

	UFUNCTION()
		void CreateGeometry(FVector Start, FVector End, float Thickness, TArray<FVector> &Vert, TArray<int> &Tria);

	UFUNCTION()
		float GridWidth();

	UFUNCTION()
		float GridHeight();

	UPROPERTY()
		class AMainPlayerController* PC;

	UPROPERTY()
		class AMainPlayerState* PS;

	UFUNCTION()
		void GenerateTerrain();

};
