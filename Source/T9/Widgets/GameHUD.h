// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "T9/Actors/Walls/WallActor.h"
#include "GameFramework/HUD.h"
#include "Engine/DataTable.h"
#include "BuildMenu_Slot.h"
#include "GameHUD.generated.h"

/**
 * 
 */


UCLASS()
class T9_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameHUD();

	//virtual void DrawHUD() override; //same as tick
	UFUNCTION(BlueprintCallable)
	void RotateSelectedBuilding(float RotationAmount);

	UFUNCTION(BlueprintCallable)
	void ShowBuildMenu();

	UFUNCTION(BlueprintCallable)
	void HideBuildMenu();

	UFUNCTION(BlueprintCallable)
		void ShowSelectMenu();

	UFUNCTION(BlueprintCallable)
		void HideSelectMenu();

	UFUNCTION(BlueprintCallable)
	void ShowInventory();

	UFUNCTION(BlueprintCallable)
	void HideInventory();

	UFUNCTION(BlueprintCallable)
		void ShowPlayerMessage();

	UFUNCTION(BlueprintCallable)
		void HidePlayerMessage();

	UFUNCTION(BlueprintCallable)
		void ShowShowItems();

	UFUNCTION(BlueprintCallable)
		void HideShowItems();

	UFUNCTION(BlueprintCallable)
		void ShowItemsForSlot(class UInventorySlot* ClickedSlot);

	UFUNCTION(BlueprintCallable)
	    void AddPlayerAlert(FString Title, FString Message, float MessageTimeout = 0);

	void SetGameObjectSelected(FHitResult Hit);

	FBuildingMenuSlot SelectedBuildMenuObject;


	UFUNCTION(BlueprintCallable)
	void SetSelectedBuildMenuObject(FBuildingMenuSlot Selection);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Menus")
		bool BuildMenuState = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Menus")
		bool InventoryState = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Menus")
		bool MessageState = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Menus")
		bool ShowItemsState = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Selection")
		class AActor* HitActor;

	UPROPERTY(VisibleAnywhere, Category = "Game Selection")
		class AActor* SelectedObject;

	UPROPERTY(VisibleAnywhere, Category = "Menu Selection")
		class UInventorySlot* SelectedSlot;

	UPROPERTY()
		class AActor* PreviewBuilding;

	UFUNCTION(BlueprintCallable, Category = "Game Selection")
		class USelectMenuWidget* GetSelectMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Selection")
		class UInventory* GetInventoryWidget();

	UFUNCTION(BlueprintCallable)
		void ShowLevelUp();

	UFUNCTION(BlueprintCallable)
		void HideLevelUp();

	UFUNCTION(BlueprintCallable)
		void PlayerLevelUp(int Level);

	UFUNCTION(BlueprintCallable)
     	ULevelUp* GetLevelUpWidget();

protected:

	FTimerHandle LevelUpTimerHandle;

	FTimerHandle PlayerAlertHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMainPlayerController* PC;

	UPROPERTY()
		class AT9GameModeBase* GameMode;

	UPROPERTY()
		class AGameGridActor* GameGrid;


	virtual void BeginPlay() override;


	UPROPERTY()
		class UBuildMenu* BuildMenuWidget;

	UPROPERTY()
		class USelectMenuWidget* SelectMenuWidget;

	UPROPERTY()
		class UHUDWidget* HUDMenuWidget;

	UPROPERTY()
		class UInventory* InventoryWidget;	
	
	UPROPERTY()
		class ULevelUp* LevelUpWidget;

	UPROPERTY()
		class UPlayerAlert* PlayerMessage;

	UPROPERTY()
		class UShowItems* ShowItems;


};
