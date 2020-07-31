// Copyright Epic Games, Inc. All Rights Reserved.


#include "T9GameModeBase.h"
#include "GameGridActor.h"
#include "CameraPawn.h"
#include "MainPlayerController.h"
#include "GameHUD.h"
#include "MainPlayerState.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>


AT9GameModeBase::AT9GameModeBase() {
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameGridActor::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0) {
		Grid = (AGameGridActor*)FoundActors[0];
	}
	DefaultPawnClass = ACameraPawn::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
	PlayerStateClass = AMainPlayerState::StaticClass();
	//GameSessionClass
	//GameStateClass
}

void AT9GameModeBase::BeginPlay()
{
	Super::BeginPlay();
}