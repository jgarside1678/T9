// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/Actors/Walls/WallActor.h"
#include "GameFramework/HUD.h"
#include "Engine/DataTable.h"
#include "GameHUD.generated.h"

/**
 * 
 */
USTRUCT()
struct FBuildingMenu : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Building;

	UPROPERTY(EditAnywhere)
		FBuildingCosts Cost;
};




UCLASS()
class T9_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameHUD();

	//virtual void DrawHUD() override; //same as tick
	void SetSelectedBuildMenuObject(FString Selection);
	void RotateSelectedBuilding(float RotationAmount);

	void ShowBuildMenu();
	void RemoveBuildMenu();

	void ShowInventory();
	void HideInventory();

	void SetGameObjectSelected(FHitResult Hit);

	FBuildingMenu* SelectedBuildMenuObject;

	UPROPERTY()
		bool BuildMenuState = false;

	UPROPERTY()
		bool InventoryState = false;

	UPROPERTY()
		class UDataTable* BuildMenuBuildings;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Selection")
		class AActor* HitActor;

	UPROPERTY(VisibleAnywhere, Category = "Game Selection")
		class AActor* SelectedObject;

	UPROPERTY()
		class AActor* PreviewBuilding;

	UFUNCTION(BlueprintCallable, Category = "Game Selection")
		class USelectMenuWidget* GetSelectMenu();



protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMainPlayerController* PC;

	UPROPERTY()
		class AT9GameModeBase* GameMode;

	UPROPERTY()
		class AGameGridActor* GameGrid;


	virtual void BeginPlay() override;


	UPROPERTY()
		class UBuildMenuWidget* BuildMenuWidget;

	UPROPERTY()
		class USelectMenuWidget* SelectMenuWidget;

	UPROPERTY()
		class UHUDWidget* HUDMenuWidget;

	UPROPERTY()
		class UInventory* InventoryWidget;



};
