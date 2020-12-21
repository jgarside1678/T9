// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Infernal_GreatAxe.h"

AItem_Infernal_GreatAxe::AItem_Infernal_GreatAxe() {
	//Damage, Health, Defence, Gather
	Modifiers = { FItemModifiersOffensive{300, 1.2}, FItemModifiersDefensive{}, FItemModifiersProduction{} };
	ItemSocket = MainHand;
	ItemName = "Infernal GreatAxe Of Kharg";
	ItemType = Weapon;
	ItemSubType = Axe;
	ItemRarity = Mythical;
	ItemEquipedTransform = FTransform(FRotator(7, 43, 15), FVector(12, -14, 6), FVector(0.7));
	ItemSheathedTransform = FTransform(FRotator(56, -170, -80), FVector(-10, 18, 2), FVector(0.5));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Sprite(TEXT("Texture2D'/Game/UI/Assets/Sprites/AxeTest.AxeTest'"));
	if (Sprite.Succeeded()) {
		ItemImage = Sprite.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/World/FantasyWeapons/meshes/SM_axe3.SM_axe3'"));
	if (Mesh.Succeeded()) {
		ItemMesh->SetWorldScale3D(FVector(0.8));
		ItemMesh->SetStaticMesh(Mesh.Object);
	}
	GoldValue = 2000;
}