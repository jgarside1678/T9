// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMenuWidget.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class ESelectTab : uint8
{

	StatsTab UMETA(DisplayName = "Stats"),
	UpgradeTab UMETA(DisplayName = "Upgrade"),
	ItemsTab UMETA(DisplayName = "Items")
};

FORCEINLINE ESelectTab& operator++(ESelectTab& d)
{
	return d = (d == ESelectTab::ItemsTab) ? ESelectTab::StatsTab : static_cast<ESelectTab>(static_cast<int>(d) + 1);
}

FORCEINLINE ESelectTab& operator--(ESelectTab& d)
{
	return d = (d == ESelectTab::StatsTab) ? ESelectTab::ItemsTab : static_cast<ESelectTab>(static_cast<int>(d) - 1);
}

UCLASS()
class T9_API USelectMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	USelectMenuWidget(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		ESelectTab CurrentTab = ESelectTab::StatsTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AGameHUD* GameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AMainPlayerController* PC;

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void UpdateMenu(AActor* Object);

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void TabLeft();

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void TabRight();

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void SetTab(ESelectTab Tab);
};
