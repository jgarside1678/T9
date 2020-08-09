// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "Engine/DataTable.h"
#include "BuildMenu_Slot.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBuildingMenuSlot : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> Building;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBuildingCosts Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool DefensiveBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ResourceBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UtilityBuilding;

};




UCLASS()
class T9_API UBuildMenu_Slot : public UUserWidget
{
	GENERATED_BODY()
public:

	UBuildMenu_Slot(const FObjectInitializer& ObjectInit);

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	//virtual bool Initialize() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AGameHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AMainPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		class AMainPlayerState* PS;

};
