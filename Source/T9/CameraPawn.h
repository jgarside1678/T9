// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS(Blueprintable)
class T9_API ACameraPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ACameraPawn();






protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USceneComponent* RootScene;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* SpringArm;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class APlayerController* PC;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UFloatingPawnMovement* CameraMovement;
	//UFUNCTION(Category = Camera)
	//	FVector GetCameraDirection();


	UFUNCTION(Category = Camera)
		void Move_XAxis(float AxisValue);
	    void Move_YAxis(float AxisValue);
		void Camera_Zoom(float AxisValue);
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		int32 ScreenSizeX;
	    int32 ScreenSizeY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float MoveDirectionX;
		float MoveDirectionY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float ScrollAmount = 1500;

};
