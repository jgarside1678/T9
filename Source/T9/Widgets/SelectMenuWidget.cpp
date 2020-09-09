// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"
#include "GameHUD.h"
#include "T9/MainPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
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
	SpawnInventory = nullptr;
	if (GameHUD && GameHUD->HitActor) SelectedActor = GameHUD->HitActor;
	if (SelectedActor) {
		SelectedBuilding = Cast<ABuildingActor>(SelectedActor);
		SelectedObjectInterface = TScriptInterface<ISelectInterface>(SelectedActor);
		if (SelectedBuilding) {
			BuildingImage->SetBrushFromTexture(SelectedBuilding->GetImage());
			SelectedInventory = SelectedBuilding->GetInventory();
			SelectedInventory->OnInventoryUpdate.AddUniqueDynamic(this, &USelectMenuWidget::InitializeSelectedInventory);
			UActorComponent* ActorComp = SelectedBuilding->GetComponentByClass(UBuildingSpawnComponent::StaticClass());
			if (ActorComp) {
				SpawnComp = (UBuildingSpawnComponent*)ActorComp;
				if (SpawnComp) {
					SpawnInventory = SpawnComp->GetInventoryComponent();
					SpawnInventory->OnInventoryUpdate.AddUniqueDynamic(this, &USelectMenuWidget::InitializeSelectedInventory);
				}
			}
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
		UpdateStatsTab();
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
	if (SelectedObjectInterface) {
		SelectedLevel->SetText(FText::FromString(FString::FromInt(SelectedObjectInterface->GetLevel())));
		SelectedName->SetText(FText::FromString(SelectedObjectInterface->GetName()));
	}
	if (SelectedBuilding) {
		struct FBuildingUpgrades BuildingUpgrades = SelectedBuilding->GetCurrentBaseStats();
		StatsName1->SetText(FText::FromString(ANSI_TO_TCHAR("Health")));
		StatsName2->SetText(FText::FromString(ANSI_TO_TCHAR("Damage")));
		StatsName3->SetText(FText::FromString(ANSI_TO_TCHAR("Defence")));
		StatsName4->SetText(FText::FromString(ANSI_TO_TCHAR("Speed")));
		StatsName5->SetText(FText::FromString(ANSI_TO_TCHAR("Range")));
		StatsBase1->SetText(FText::FromString(FString::FromInt(BuildingUpgrades.MaxHealth)));
		StatsBase2->SetText(FText::FromString(FString::FromInt(BuildingUpgrades.Attack.Damage)));
		StatsBase3->SetText(FText::FromString(FString::FromInt(BuildingUpgrades.Defence)));
		StatsBase4->SetText(FText::FromString(FString::FromInt(BuildingUpgrades.Attack.AttackSpeed)));
		StatsBase5->SetText(FText::FromString(FString::FromInt(BuildingUpgrades.Attack.AttackRangeMultipler)));
		StatsModified1->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetMaxHealth() - BuildingUpgrades.MaxHealth)));
		StatsModified2->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetDamage() - BuildingUpgrades.Attack.Damage)));
		StatsModified3->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetDefence() - BuildingUpgrades.Defence)));
		StatsModified4->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentBaseStats().Attack.AttackSpeed - BuildingUpgrades.Attack.AttackSpeed)));
		StatsModified5->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentBaseStats().Attack.AttackRangeMultipler - BuildingUpgrades.Attack.AttackRangeMultipler)));
		if (SpawnComp && SpawnComp->ActorsSpawned[0]) {
			AAlliance_ResourceGatherer* ResourceCharacter = (AAlliance_ResourceGatherer*)SpawnComp->ActorsSpawned[0];
			StatsName1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Amount")));
			StatsName2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Max Inventory")));
			StatsName3_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Damage")));
			StatsName4_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Health")));
			StatsName5_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Armour")));
			if (SpawnComp->ActorsSpawned[0]) {
				StatsBase3_Character->SetText(FText::FromString(FString::FromInt(SpawnComp->ActorsSpawned[0]->GetCurrentBaseStats().BaseDamage)));
				StatsBase4_Character->SetText(FText::FromString(FString::FromInt(SpawnComp->ActorsSpawned[0]->GetCurrentBaseStats().MaxHealth)));
				StatsBase5_Character->SetText(FText::FromString(FString::FromInt(SpawnComp->ActorsSpawned[0]->GetCurrentBaseStats().Armour)));
				StatsModified3_Character->SetText(FText::FromString(FString::FromInt(SpawnComp->ActorsSpawned[0]->GetDamage())));
				StatsModified4_Character->SetText(FText::FromString(FString::FromInt(SpawnComp->ActorsSpawned[0]->GetMaxHealth())));
				StatsModified5_Character->SetText(FText::FromString(FString::FromInt(SpawnComp->ActorsSpawned[0]->GetArmour())));
			}
			if (ResourceCharacter) {
				StatsBase1_Character->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetGathererBaseStats().GatherAmount)));
				StatsBase2_Character->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetGathererBaseStats().MaxResourceInventory)));
				StatsModified1_Character->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetGatherAmount())));
				StatsModified2_Character->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetMaxResourceInventory())));
			}
			else {
				StatsBase1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
				StatsBase2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
				StatsModified1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
				StatsModified2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			}
		}
		else {
			StatsName1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Amount")));
			StatsName2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Max Inventory")));
			StatsName3_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Damage")));
			StatsName4_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Health")));
			StatsName5_Character->SetText(FText::FromString(ANSI_TO_TCHAR("Gatherer Armour")));
			StatsBase1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsBase2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsBase3_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsBase4_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsBase5_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsModified1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsModified2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsModified3_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsModified4_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
			StatsModified5_Character->SetText(FText::FromString(ANSI_TO_TCHAR("N/A")));
		}

	}
	else {
		//Resource Actors
		StatsName1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName5->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase5->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified1->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified2->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified3->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified5->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName3_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName4_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsName5_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase3_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase4_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsBase5_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified1_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified2_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified3_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified4_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StatsModified5_Character->SetText(FText::FromString(ANSI_TO_TCHAR("")));
	}
}




void USelectMenuWidget::UpdateUprgadesTab()
{
	if (SelectedBuilding) {
		HealthOld->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentBaseStats().MaxHealth)));
		HealthNew->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().MaxHealth)));
		ArmourOld->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentBaseStats().Defence)));
		ArmourNew->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Defence)));
		GoldAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Cost.Gold)));
		WoodAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Cost.Wood)));
		StoneAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Cost.Stone)));
		FoodAmount->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Cost.Food)));
		if (ADefensiveBuildingActor* Defensive = Cast<ADefensiveBuildingActor>(SelectedBuilding)) {
			UpgradesName1->SetText(FText::FromString(ANSI_TO_TCHAR("Damage")));
			UpgradesName2->SetText(FText::FromString(ANSI_TO_TCHAR("Speed")));
			UpgradesName3->SetText(FText::FromString(ANSI_TO_TCHAR("Range")));
			UpgradesName4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
			UpgradesOld1->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentBaseStats().Attack.Damage)));
			UpgradesOld2->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentBaseStats().Attack.AttackSpeed)));
			UpgradesOld3->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetCurrentBaseStats().Attack.AttackRangeMultipler)));
			UpgradesOld4->SetText(FText::FromString(ANSI_TO_TCHAR("")));
			UpgradesNew1->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Attack.Damage)));
			UpgradesNew2->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Attack.AttackSpeed)));
			UpgradesNew3->SetText(FText::FromString(FString::FromInt(SelectedBuilding->GetUpgradeBaseStats().Attack.AttackRangeMultipler)));
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
					UpgradesOld1->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetGathererBaseStats().GatherAmount)));
					UpgradesOld2->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetGathererBaseStats().MaxResourceInventory)));
					UpgradesOld3->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentBaseStats().BaseDamage)));
					UpgradesOld4->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetCurrentBaseStats().MaxHealth)));
					UpgradesNew1->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetGathererUpgradeStats().GatherAmount)));
					UpgradesNew2->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetGathererUpgradeStats().MaxResourceInventory)));
					UpgradesNew3->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetUpgradeBaseStats().BaseDamage)));
					UpgradesNew4->SetText(FText::FromString(FString::FromInt(ResourceCharacter->GetUpgradeBaseStats().MaxHealth)));
				}
			}
		}
	}
	else {
		GoldAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		WoodAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		StoneAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		FoodAmount->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		HealthOld->SetText(FText::FromString(ANSI_TO_TCHAR("")));
		HealthNew->SetText(FText::FromString(ANSI_TO_TCHAR("")));
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
	InventoryBox_Character->ClearChildren();
	if (SelectedInventory) {
		TArray<FSlot> SelectedInventoryItems = SelectedInventory->GetItems();
		for (int x = 0; x < SelectedInventoryItems.Num(); x++) {
			UInventorySlot* NewSlot = Cast<UInventorySlot>(CreateWidget(InventoryBox, SelectSlot));
			NewSlot->InventorySlotInit(SelectedInventoryItems[x], SelectedBuilding->GetInventory());
			InventoryBox->AddChild(NewSlot);
		}
	}
	if (SpawnInventory) {
		TArray<FSlot> SelectedInventoryItems = SpawnInventory->GetItems();
		for (int x = 0; x < SelectedInventoryItems.Num(); x++) {
			UInventorySlot* NewSlot = Cast<UInventorySlot>(CreateWidget(InventoryBox_Character, SelectSlot));
			NewSlot->InventorySlotInit(SelectedInventoryItems[x], SpawnInventory);
			InventoryBox_Character->AddChild(NewSlot);
		}
	}
}

