// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UBuildMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UBuildMenuWidget(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AMainPlayerController* PC;

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
	void SelectBuilding(FString Selection);

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
	void RotateSelection();
};
