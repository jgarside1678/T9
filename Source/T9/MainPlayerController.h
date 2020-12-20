// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "T9/Widgets/GameHUD.h"
#include "T9/Widgets/BuildMenu_Slot.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS()
class T9_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void OpenCloseBuildMenu();

	void ToggleInventory();

	void ToggleHUD();

	AGameHUD* HUDPointer;


	UFUNCTION(BlueprintCallable)
		class AGameGridActor* GetGrid();

	UFUNCTION(BlueprintCallable)
	    void CreateAlert(FString Title, FString Message, float MessageTimeout = 0);


protected:

	void SelectPressed();

	void SelectReleased();

	void SelectInteract();

	void MiddleMouseButtonPressed();
	void MiddleMouseButtonReleased();

	float CameraRotationZ = 0;

	class ACameraPawn* Camera;

	bool CameraRotating = false;

	void MouseMove(float axis);

	UPROPERTY()
		class AT9GameModeBase* GameMode;

	UPROPERTY()
		class AMainPlayerState* PS;


	UPROPERTY()
		class AGameGridActor* GameGrid;


};
