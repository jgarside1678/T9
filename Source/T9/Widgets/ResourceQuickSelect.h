// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceQuickSelect.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UResourceQuickSelect : public UUserWidget
{
	GENERATED_BODY()
public:

	UResourceQuickSelect(const FObjectInitializer& ObjectInit);

	UFUNCTION(BlueprintCallable)
		void Init(class AResourceActor* MenuResource);

protected:


	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	UPROPERTY()
		class AResourceActor* Resource;

	UPROPERTY()
		TArray<class UTexture2D*> TierBackgrounds;

	//UPROPERTY()
	//	class UTexture2D* Tier1Background;

	//UPROPERTY()
	//	class UTexture2D* Tier2Background;

	//UPROPERTY()
	//	class UTexture2D* Tier3Background;

	UPROPERTY(meta = (BindWidget))
		class UImage* ResourceBackgroundImage;

	UPROPERTY(meta = (BindWidget))
		class UImage* ResourceImage;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ResourceTitle;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ResourceSpawnCount;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ResourceMultiplier;

};
