// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Infernal_Scimitar.h"


AItem_Infernal_Scimitar::AItem_Infernal_Scimitar() {
	Modifiers = { 150, 1 };
	ItemSocket = MainHand;
	ItemName = "Infernal Scimitar Of Zhurk";
	ItemType = Weapon;
	ItemSubType = Axe;
	ItemRarity = Legendary;
	ItemEquipedTransform = FTransform(FRotator(7, 43, 15), FVector(12, -14, 6), FVector(0.7));
	ItemSheathedTransform = FTransform(FRotator(56, -170, -80), FVector(-10, 18, 2), FVector(0.5));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Sprite(TEXT("Texture2D'/Game/Assets/UI/InfernalScimitarImage.InfernalScimitarImage'"));
	if (Sprite.Succeeded()) {
		ItemImage = Sprite.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/FantasyWeapons/meshes/SM_sword3.SM_sword3'"));
	if (Mesh.Succeeded()) {
		ItemMesh->SetWorldScale3D(FVector(0.8));
		ItemMesh->SetStaticMesh(Mesh.Object);
	}
	GoldValue = 1400;
}