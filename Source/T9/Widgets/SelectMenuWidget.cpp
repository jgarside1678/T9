// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/PanelWidget.h"
#include "Components/WrapBox.h"
#include "InventorySlot.h"
#include "T9/Actors/Components/InventoryComponent.h"
#include "T9/Characters/Alliance/Alliance_ResourceGatherer.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/Actors/Buildings/DefensiveBuildingActor.h"

USelectMenuWidget::USelectMenuWidget(const FObjectInitializer& ObjectInit) : Super(ObjectInit)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> SpriteOn(TEXT("Texture2D'/Game/Assets/TheStone/PNG/17_Components/radiobtn_on.radiobtn_on'"));
	if (SpriteOn.Succeeded()) {
		TabButtonImageOn = SpriteOn.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> SpriteOff(TEXT("Texture2D'/Game/Assets/TheStone/PNG/17_Components/radiobtn_off.radiobtn_off'"));
	if (SpriteOff.Succeeded()) {
		TabButtonImageOff = SpriteOff.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SlotBP(TEXT("WidgetBlueprint'/Game/UI/Select_Slot_BP.Select_Slot_BP_C'"));
	if (SlotBP.Succeeded()) {
		SelectSlot = SlotBP.Class;
	}
}

void USelectMenuWidget::NativeConstruct()
{
	SpawnComp = nullptr;
	if (GameHUD && GameHUD->HitActor) SelectedActor = GameHUD->HitActor;
	if (SelectedActor) {
		SelectedBuilding = Cast<ABuildingActor>(SelectedActor);
		SelectedObjectInterface = TScriptInterface<ISelectInterface>(SelectedActor);
		if (SelectedBuilding) {
			SelectedInventory = SelectedBuilding->GetInventory();
			UActorComponent* ActorComp = SelectedBuilding->GetComponentByClass(UBuildingSpawnComponent::StaticClass());
			if (ActorComp) SpawnComp = (UBuildingSpawnComponent*)ActorComp;
		}
		else SelectedInventory = nullptr;
	}
	Super::NativeConstruct();
}


void USelectMenuWidget::NativePreConstruct() {
	if (!PC) 	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	if(PC) GameHUD = Cast<AGameHUD>(PC->GetHUD());
	Super::NativePreConstruct();
}

void USelectMenuWidget::UpdateMenu(AActor* Object)
{
}

void USelectMenuWidget::TabLeft()
{
	--CurrentTab;
}

void USelectMenuWidget::TabRight()
{
	++CurrentTab;
}

void USelectMenuWidget::SetTab(ESelectTab Tab)
{
}

static void ChangeButtonImage(UButton* Button, UTexture2D* Image) {
	Button->WidgetStyle.Normal.SetResourceObject(Image);
	Button->WidgetStyle.Hovered.SetResourceObject(Image);
	Button->WidgetStyle.Pressed.SetResourceObject(Image);
}

void USelectMenuWidget::ChangeTab() {
	if (CurrentTab == ESelectTab::StatsTab) {
		CurrentOverlayText->SetText(FText::FromString(ANSI_TO_TCHAR("Stats")));
		ChangeButtonImage(OverlayStatsButton, TabButtonImageOn);
		ChangeButtonImage(OverlayUpgradesButton, TabButtonImageOff);
		ChangeButtonImage(OverlayItemsButton, TabButtonImageOff);
		Stats->SetVisibility(ESlateVisibility::Visible);
		Upgrades->SetVisibility(ESlateVisibility::Hidden);
		Items->SetVisibility(ESlateVisibility::Hidden);
	}
	else if(CurrentTab == ESelectTab::UpgradeTab){
		CurrentOverlayText->SetText(FText::FromString(ANSI_TO_TCHAR("Upgrade")));
		ChangeButtonImage(OverlayStatsButton, TabButtonImageOff);
		ChangeButtonImage(OverlayUpgradesButton, TabButtonImageOn);
		ChangeButtonImage(OverlayItemsButton, TabButtonImageOff);
		Stats->SetVisibility(ESlateVisibility::Hidden);
		Upgrades->SetVisibility(ESlateVisibility::Visible);
		Items->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		CurrentOverlayText->SetText(FText::FromString(ANSI_TO_TCHAR("Items")));
		ChangeButtonImage(OverlayStatsButton, TabButtonImageOff);
		ChangeButtonImage(OverlayUpgradesButton, TabButtonImageOff);
		ChangeButtonImage(OverlayItemsButton, TabButtonImageOn);
		Stats->SetVisibility(ESlateVisibility::Hidden);
		Upgrades->SetVisibility(ESlateVisibility::Hidden);
		Items->SetVisibility(ESlateVisibility::Visible);
	}
}

void USelectMenuWidget::UpdateStatsTab()
{
	SelectedLevel->SetText(FText::FromString(FString::FromInt(SelectedObjectInterface->GetLevel())));
	SelectedName->SetText(FText::FromString(SelectedObjectInterface->GetName()));
	if (SelectedBuilding) {
		if (ADefensiveBuildingActor* Defensive = Cast<ADefensiveBuildingActor>(SelectedBuilding)) {
			StatsName1->SetText(FText::FromString(ANSI_TO_TCHAR("Damage")));
			StatsName2->SetText(FText::FromString(ANSI_TO_TCHAR("Speed")));
			StatsName3->SetText(FText::FromString(ANSI_TO_TCHAR("Range")));
			StatsName4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
			StatsBase1->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Attack.Damage)));
			StatsBase2->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Attack.AttackSpeed)));
			StatsBase3->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Attack.AttackRangeMultipler)));
			StatsBase4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		}
		else {
			//Resource Buildings
			if (SpawnComp && SpawnComp->ActorsSpawned[0]) {
				AAlliance_ResourceGatherer* ResourceCharacter = (AAlliance_ResourceGatherer*)SpawnComp->ActorsSpawned[0];
				StatsName1->SetText(FText::FromString(ANSI_TO_TCHAR("Gather Amount")));
				StatsName2->SetText(FText::FromString(ANSI_TO_TCHAR("Max Inventory")));
				StatsName3->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Damage")));
				StatsName4->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Health")));
				if (ResourceCharacter) {
					StatsBase1->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().GatherAmount)));
					StatsBase2->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().MaxResourceInventory)));
					StatsBase3->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().Damage)));
					StatsBase4->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().MaxHealth)));
				}
			}
		}
	}
	else {
		//Resource Actors
		StatsName1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase4->SetText(FText::FromString(ANSI_TO_TCHAR("")));

	}
}




void USelectMenuWidget::UpdateUprgadesTab()
{
	if (SelectedBuilding) {
		HealthOld->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().MaxHealth)));
		HealthNew->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeStats().MaxHealth)));
		GoldAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Cost.Gold)));
		WoodAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Cost.Wood)));
		StoneAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Cost.Stone)));
		FoodAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Cost.Food)));
		if (ADefensiveBuildingActor* Defensive = Cast<ADefensiveBuildingActor>(SelectedBuilding)) {
			UpgradesName1->SetText(FText::FromString(ANSI_TO_TCHAR("Damage")));
			UpgradesName2->SetText(FText::FromString(ANSI_TO_TCHAR("Speed")));
			UpgradesName3->SetText(FText::FromString(ANSI_TO_TCHAR("Range")));
			UpgradesName4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
			UpgradesOld1->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Attack.Damage)));
			UpgradesOld2->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Attack.AttackSpeed)));
			UpgradesOld3->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentStats().Attack.AttackRangeMultipler)));
			UpgradesOld4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
			UpgradesNew1->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeStats().Attack.Damage)));
			UpgradesNew2->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeStats().Attack.AttackSpeed)));
			UpgradesNew3->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeStats().Attack.AttackRangeMultipler)));
			UpgradesNew4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		}
		else {
			//Resource Buildings
			if (SpawnComp && SpawnComp->ActorsSpawned[0]) {
				AAlliance_ResourceGatherer* ResourceCharacter = (AAlliance_ResourceGatherer*)SpawnComp->ActorsSpawned[0];
				UpgradesName1->SetText(FText::FromString(ANSI_TO_TCHAR("Gather Amount")));
				UpgradesName2->SetText(FText::FromString(ANSI_TO_TCHAR("Max Inventory")));
				UpgradesName3->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Damage")));
				UpgradesName4->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Health")));
				if (ResourceCharacter) {
					UpgradesOld1->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().GatherAmount)));
					UpgradesOld2->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().MaxResourceInventory)));
					UpgradesOld3->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().Damage)));
					UpgradesOld4->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentStats().MaxHealth)));
					UpgradesNew1->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetUpgradeStats().GatherAmount)));
					UpgradesNew2->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetUpgradeStats().MaxResourceInventory)));
					UpgradesNew3->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetUpgradeStats().Damage)));
					UpgradesNew4->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetUpgradeStats().MaxHealth)));
				}
			}
		}
	}
	else {
		GoldAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		WoodAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StoneAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		FoodAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		HealthOld->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
		HealthNew->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
		UpgradesName1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesName2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesName3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesName4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesOld1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesOld2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesOld3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesOld4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesNew1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesNew2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesNew3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		UpgradesNew4->SetText(FText::FromString(ANSI_TO_TCHAR("")));

	}
}

void USelectMenuWidget::UpdateItemsTab()
{
}

void USelectMenuWidget::InitializeSelectedInventory()
{
	InventoryBox->ClearChildren();
	if (SelectedInventory) {
		TArray<FSlot> SelectedInventoryItems = SelectedInventory->GetItems();
		for (int x = 0; x < SelectedInventoryItems.Num(); x++) {
			UInventorySlot* NewSlot = Cast<UInventorySlot>(CreateWidget(InventoryBox, SelectSlot));
			NewSlot->InventorySlotInit(SelectedInventoryItems[x], SelectedBuilding->GetInventory());
			InventoryBox->AddChild(NewSlot);
		}
	}
	if (SpawnComp) {
		SpawnInventory = SpawnComp->GetInventoryComponent();
		if (SpawnInventory) {
			TArray<FSlot> SelectedInventoryItems = SpawnInventory->GetItems();
			for (int x = 0; x < SelectedInventoryItems.Num(); x++) {
				UInventorySlot* NewSlot = Cast<UInventorySlot>(CreateWidget(InventoryBox, SelectSlot));
				NewSlot->InventorySlotInit(SelectedInventoryItems[x], SpawnInventory);
				InventoryBox->AddChild(NewSlot);
			}
		}
	}
}

