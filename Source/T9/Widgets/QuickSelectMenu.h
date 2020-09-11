// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UQuickSelectMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	UQuickSelectMenu(const FObjectInitializer& ObjectInit);

	UFUNCTION(BlueprintCallable)
		void Init(class ABuildingActor* Building);

	UFUNCTION(BlueprintCallable)
		void MoveBuilding();

	UFUNCTION(BlueprintCallable)
		void UpgradeRestoreBuilding();

	UFUNCTION(BlueprintCallable)
		void InfoBuilding();

	UFUNCTION(BlueprintCallable)
		void StoreBuilding();

	UFUNCTION(BlueprintCallable)
		void SetRestoreImage();

	UFUNCTION(BlueprintCallable)
		void SetUpgradeImage();

protected:

	UPROPERTY()
		class ABuildingActor* SelectedBuilding;

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	UPROPERTY()
		class AMainPlayerController* PC;

	UPROPERTY()
		class AMainPlayerState* PS;

	UPROPERTY()
		class AGameHUD* HUD;

	UPROPERTY(meta = (BindWidget))
		class UImage* RestoreUpgradeImage;

	UPROPERTY(meta = (BindWidget))
		class UButton* Move;

	UPROPERTY(meta = (BindWidget))
		class UButton* RestoreUpgrade;


	UPROPERTY(meta = (BindWidget))
		class UButton* Info;

	UPROPERTY(meta = (BindWidget))
		class UButton* Store;

	UPROPERTY()
		class UTexture2D* RestoreImage;

	UPROPERTY()
		class UTexture2D* UpgradeImage;
};
