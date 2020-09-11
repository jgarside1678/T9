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

	UPROPERTY()
		class AResourceActor* Resource;

};
