// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerAlert.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UPlayerAlert : public UUserWidget
{
	GENERATED_BODY()
public:

	UPlayerAlert(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	void SetAlertContent(FString Title, FString Message);

protected:


	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MessageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert")
		float TimeoutTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert")
		class AGameHUD* GameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert")
		class AMainPlayerState* PS;
};
