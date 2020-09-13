// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceQuickSelect.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UResourceQuickSelect::UResourceQuickSelect(const FObjectInitializer& ObjectInit) : Super(ObjectInit) {
	static ConstructorHelpers::FObjectFinder<UTexture2D> Tier1(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/17_Components/mission_frame_brown.mission_frame_brown'"));
	if (Tier1.Succeeded()) {
		TierBackgrounds.Add(Tier1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> Tier2(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/17_Components/skill_frame_sliver.skill_frame_sliver'"));
	if (Tier2.Succeeded()) {
		TierBackgrounds.Add(Tier2.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> Tier3(TEXT("Texture2D'/Game/UI/Assets/TheStone/PNG/17_Components/skill_frame_yellow.skill_frame_yellow'"));
	if (Tier3.Succeeded()) {
		TierBackgrounds.Add(Tier3.Object);
	}
}

void UResourceQuickSelect::Init(AResourceActor* MenuResource)
{
	if (MenuResource) {
		Resource = MenuResource;
		FResourceTierStats ResourceStats = MenuResource->GetResourceStats();
		ResourceTitle->SetText(FText::FromString(ResourceStats.Name));
		ResourceSpawnCount->SetText(FText::FromString(FString::FromInt(Resource->GetSpawnedUnits())));
		ResourceMultiplier->SetText(FText::FromString(FString::SanitizeFloat(ResourceStats.ResourceGatherMultiplier)));
		ResourceBackgroundImage->SetBrushFromTexture(TierBackgrounds[MenuResource->GetTier()]);
	}
}

void UResourceQuickSelect::NativeConstruct()
{
	if(Resource) ResourceSpawnCount->SetText(FText::FromString(FString::FromInt(Resource->GetSpawnedUnits())));
}

void UResourceQuickSelect::NativePreConstruct()
{
}
