// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "MainPlayerState.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "T9/Actors/GameGridActor.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "T9GameModeBase.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "CameraPawn.h"
#include "Engine/DataTable.h"

static TSubclassOf<ABuildingActor> ObjectToSpawn;

AMainPlayerController::AMainPlayerController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	UWorld* World = GetWorld();
	if (World) {
		GameMode = (AT9GameModeBase*)UGameplayStatics::GetGameMode(World);
		if (GameMode != nullptr) {
			GameGrid = GameMode->Grid;
		}
	}
}

void AMainPlayerController::BeginPlay()
{
	HUDPointer = Cast<AGameHUD>(GetHUD());
	PS = (AMainPlayerState*)PlayerState;
	Camera = Cast<ACameraPawn>(GetPawn());
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AMainPlayerController::SelectPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &AMainPlayerController::SelectReleased);

	InputComponent->BindAction("RightMouseClick", IE_Released, this, &AMainPlayerController::SelectInteract);

	InputComponent->BindAction("Key_E", IE_Pressed, this, &AMainPlayerController::OpenCloseBuildMenu);

	InputComponent->BindAction("Tab", IE_Pressed, this, &AMainPlayerController::ToggleInventory);

	InputComponent->BindAction("Key_P", IE_Pressed, this, &AMainPlayerController::ToggleHUD);

	InputComponent->BindAction("MiddleMouse", IE_Pressed, this, &AMainPlayerController::MiddleMouseButtonPressed);
	InputComponent->BindAction("MiddleMouse", IE_Released, this, &AMainPlayerController::MiddleMouseButtonReleased);

	InputComponent->BindAxis("MouseMoving", this, &AMainPlayerController::MouseMove);

}

void AMainPlayerController::MiddleMouseButtonPressed() {
	CameraRotating = true;

}
void AMainPlayerController::MiddleMouseButtonReleased() {
	CameraRotating = false;
}

void AMainPlayerController::OpenCloseBuildMenu()
{
	if (HUDPointer->BuildMenuState) {
		HUDPointer->HideBuildMenu();
	}
	else HUDPointer->ShowBuildMenu();
}

void AMainPlayerController::ToggleInventory()
{
	if (HUDPointer->InventoryState) {
		HUDPointer->HideInventory();
	}
	else HUDPointer->ShowInventory();
}

void AMainPlayerController::ToggleHUD()
{
	if (HUDPointer->HUDState) {
		HUDPointer->HideMainHUD();
	}
	else HUDPointer->ShowMainHUD();
}

void AMainPlayerController::SelectPressed() {
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel2, true, Hit);
	//bool ValidHit = GetHitResultUnderCursorByChannel((ETraceTypeQuery)ECC_GameTraceChannel2, true, Hit);
	if (Hit.Actor.IsValid()) {
		HUDPointer->SetGameObjectSelected(Hit);
	}
}


void AMainPlayerController::SelectReleased() {

}


void AMainPlayerController::MouseMove(float axis) {
	if (CameraRotating && Camera) {
		CameraRotationZ += axis*2;
		Camera->SpringArm->SetRelativeRotation(FRotator(-40, CameraRotationZ, 0));
	}
	else if (HUDPointer->BuildMenuState == true) {
		FHitResult Hit;
		bool ValidHit = GetHitResultUnderCursorByChannel((ETraceTypeQuery)ECC_Visibility, true, Hit);
		if (GameGrid != nullptr) {
			//if (GameGrid->CheckGridLocation(Hit.Location, 1, 1)) {
				GameGrid->ToggleSelectionTile(true);
				bool ValidTile = GameGrid->LocationToTile(Hit.Location);
				if (ValidTile) GameGrid->SetSelectedTile();
				//if (HUDPointer->SelectedBuildMenuObject) GameGrid->MovePreviewObject(Hit.Location);
			//}
			else {
				GameGrid->ToggleSelectionTile(false);
			}
		}
	}
}

void AMainPlayerController::SelectInteract() {
	if ((HUDPointer->BuildMenuState) && (GameGrid != nullptr) && (PS != nullptr)) {
		if (HUDPointer->SelectedBuildMenuObject.Building != NULL) {
				ABuildingActor* Building = Cast<ABuildingActor>(HUDPointer->PreviewBuilding);
				if (Building) {
					if ((PS->GetBuildingCount(Building->GetName()) < PS->GetMaxBuildingCount(Building->GetName())) && PS->ResourceCheck(Building->GetCost())) {
						GameGrid->BuildBuildingOnTile(HUDPointer->SelectedBuildMenuObject);
					}
					else CreateAlert("Error", "Conditions to build this building were not met.", 5);
				}
		}
	}
	else if (HUDPointer->SelectedAllianceCharacter) {
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_GameTraceChannel2, true, Hit);
		//bool ValidHit = GetHitResultUnderCursorByChannel((ETraceTypeQuery)ECC_GameTraceChannel2, true, Hit);
		if (Hit.Actor.IsValid()) {
			HUDPointer->SelectedAllianceCharacter->Command(Hit);
		}
	}
}


AGameGridActor* AMainPlayerController::GetGrid() {
	return GameGrid;
}

void AMainPlayerController::CreateAlert(FString Title, FString Message, float MessageTimeout)
{
	if (HUDPointer) HUDPointer->AddPlayerAlert(Title, Message, MessageTimeout);
}
