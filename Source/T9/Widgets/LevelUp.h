// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUp.generated.h"

/**
 * 
 */
UCLASS()
class T9_API ULevelUp : public UUserWidget
{
	GENERATED_BODY()
public:	

	ULevelUp(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	void LevelUpInit(int Level);

	void CreatePreviewWidget(class UTexture2D* Image, int Amount);

protected:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* NewLevel;

	UPROPERTY(meta = (BindWidget))
		class UImage* SpinningEffect;

	UPROPERTY(meta = (BindWidget))
		class UWrapBox* NewItemsBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUpMain")
		int Angle = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUpMain")
		TSubclassOf<UUserWidget> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUpMain")
		class AGameHUD* GameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUpMain")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUpMain")
		class AMainPlayerState* PS;
};
  