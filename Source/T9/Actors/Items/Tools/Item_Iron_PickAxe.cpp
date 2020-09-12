// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Iron_PickAxe.h"

AItem_Iron_PickAxe::AItem_Iron_PickAxe() {
	Modifiers = {30, 1, 50, 1, 5000, 1, 10, 1};
	ItemSocket = MainHand;
	ItemName = "Sindering Axe";
	ItemType = Tool;
	ItemSubType = Axe;
	ItemRarity = Legendary;
	ItemEquipedTransform = FTransform(FRotator(7,43, 15), FVector(12,-14,6), FVector(0.7));
	ItemSheathedTransform = FTransform(FRotator(56,-170,-80), FVector(-10,18,2), FVector(0.5));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Sprite(TEXT("Texture2D'/Game/UI/Assets/Sprites/AxeTest.AxeTest'"));
	if (Sprite.Succeeded()) {
		ItemImage = Sprite.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/FantasyWeapons/meshes/SM_axe3.SM_axe3'"));
	if (Mesh.Succeeded()) {
		ItemMesh->SetWorldScale3D(FVector(0.8));
		ItemMesh->SetStaticMesh(Mesh.Object);
		//ItemMesh->SetRelativeLocation(FVector(63, -23, 0));
	}
	GoldValue = 40;
}