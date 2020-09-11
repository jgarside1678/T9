// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCharacter.h"
#include "ResourceActor.h"

// Sets default values
AResourceCharacter::AResourceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResourceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AResourceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AResourceCharacter::Init(AResourceActor* OwningResource, FVector SpawnLocation)
{
	ParentResource = OwningResource;
	InitialLocation = SpawnLocation;
	if (!GetController()) {
		FTimerHandle ControllerTimerHandle;
		GetWorldTimerManager().SetTimer(ControllerTimerHandle, this, &AResourceCharacter::SpawnDefaultController, 2, false, 2);
	}
}

bool AResourceCharacter::CheckIfDead() {
	return Dead;
}

AResourceActor* AResourceCharacter::GetParentResource()
{
	return ParentResource;
}

void AResourceCharacter::SetSelected()
{
	ParentResource->SetSelected();
}

void AResourceCharacter::SetUnSelected()
{
	ParentResource->SetUnSelected();
}
