// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "MainPlayerState.h"
#include "HealthBarWidget.h"

AEnemyCharacter::AEnemyCharacter() {
	TargetBuildings = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("WidgetBlueprint'/Game/UI/EnemyHealthBar.EnemyHealthBar_C'"));
	if (widget.Succeeded()) {
		WidgetClass = widget.Class;
	}
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();
	if (PS) PS->SpawnedEnemyCharacters.Add(this);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}