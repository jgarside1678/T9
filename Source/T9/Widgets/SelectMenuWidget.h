// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T9/Interfaces/SelectInterface.h"
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

	virtual void NativePreConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
		ESelectTab CurrentTab = ESelectTab::StatsTab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
		class AGameHUD* GameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
		class AActor* SelectedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
		class ABuildingActor* SelectedBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
		TScriptInterface<ISelectInterface> SelectedObjectInterface;

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void UpdateMenu(AActor* Object);

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void TabLeft();

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void TabRight();

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void SetTab(ESelectTab Tab);

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void ChangeTab();

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void UpdateStatsTab();

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void UpdateUprgadesTab();

	UFUNCTION(BlueprintCallable, Category = "WidgetFunctions")
		void UpdateItemsTab();

protected:
	//Tab Orange Buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
	    class UTexture2D* TabButtonImageOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selectwidget")
		class UTexture2D* TabButtonImageOff;

	//Buttons

	UPROPERTY(meta = (BindWidget))
	    class UButton* OverlayStatsButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* OverlayUpgradesButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* OverlayItemsButton;

	//TextBlocks

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentOverlayText;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SelectedLevel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SelectedName;

	//Overlays

	UPROPERTY(meta = (BindWidget))
		class UOverlay* Items;

	//Stats


	UPROPERTY(meta = (BindWidget))
		class UOverlay* Stats;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsName1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsName2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsName3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsName4;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsBase1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsBase2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsBase3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsBase4;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsModified1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsModified2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsModified3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatsModified4;

	//Upgrade

	UPROPERTY(meta = (BindWidget))
		class UOverlay* Upgrades;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Health;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HealthNew;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HealthOld;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesName1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesName2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesName3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesName4;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesOld1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesOld2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesOld3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesOld4;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesNew1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesNew2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesNew3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UpgradesNew4;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GoldAmount;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* WoodAmount;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StoneAmount;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* FoodAmount;

};
