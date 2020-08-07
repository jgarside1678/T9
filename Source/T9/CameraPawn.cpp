// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-40, 0, 0));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);

	SpringArm->SetRelativeLocation(FVector(0, 0, 0));

	CameraMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController());
	if (PC) {
		PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
	}
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CameraMovement) {
		CameraMovement->Deceleration = 100020;
		CameraMovement->Acceleration = 100220;
		CameraMovement->MaxSpeed = ScrollAmount/200 *200 + 1200;
	}
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &ACameraPawn::Move_XAxis);
	InputComponent->BindAxis("MoveBackward", this, &ACameraPawn::Move_YAxis);
	InputComponent->BindAxis("MouseWheel", this, &ACameraPawn::Camera_Zoom);

}


void ACameraPawn::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	if ((Controller != NULL) &&(AxisValue != 0.0f))
	{
		 //find out which way is forward
		const FRotator Rotation = SpringArm->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//CameraMovement->AddInputVector(Direction, true);
		AddMovementInput(Direction, AxisValue);
	}
}

void ACameraPawn::Move_YAxis(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = SpringArm->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void ACameraPawn::Camera_Zoom(float AxisValue)
{
	ScrollAmount += AxisValue * 100.0f;
	//if (ScrollAmount > 1300) ScrollAmount = 1300;
	if (ScrollAmount < 0) ScrollAmount = 0;
	SpringArm->TargetArmLength = ScrollAmount;
	// Move at 100 units per second right or left
}
