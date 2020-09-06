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
		void Init(class AActor* Selected);

	UFUNCTION(BlueprintCallable)
		void MoveBuilding();

	UFUNCTION(BlueprintCallable)
		void UpgradeRestoreBuilding();

	UFUNCTION(BlueprintCallable)
		void InfoBuilding();

	UFUNCTION(BlueprintCallable)
		void StoreBuilding();

protected:

	UPROPERTY()
		class ABuildingActor* SelectedBuilding;

	UPROPERTY()
		class AResourceActor* SelectedResource;

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	UPROPERTY()
		class AMainPlayerController* PC;

	UPROPERTY()
		class AMainPlayerState* PS;

	UPROPERTY()
		class AGameHUD* HUD;
};
