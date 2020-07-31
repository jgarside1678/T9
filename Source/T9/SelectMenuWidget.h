// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMenuWidget.generated.h"

/**
 * 
 */


UENUM()
enum SelectTab
{
	StatsTab UMETA(DisplayName = "Stats"),
	ItemsTab UMETA(DisplayName = "Items"),
	UpgradeTab UMETA(DisplayName = "Upgrade")
};

UCLASS()
class T9_API USelectMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	USelectMenuWidget(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TEnumAsByte<SelectTab> CurrentTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AGameHUD* GameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AMainPlayerController* PC;

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void UpdateMenu(AActor* Object);

};
