// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpItem.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ULevelUpItem : public UUserWidget
{
	GENERATED_BODY()
public:

	ULevelUpItem(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	class AGameHUD* HUD;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	class AMainPlayerController* PC;

	UFUNCTION(BlueprintCallable)
		void Init(class UTexture2D* Image, int Amount);

protected:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemAmount;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;
};
