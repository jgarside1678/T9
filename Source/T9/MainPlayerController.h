// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "GameHUD.h"
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

	AGameHUD* HUDPointer;

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
