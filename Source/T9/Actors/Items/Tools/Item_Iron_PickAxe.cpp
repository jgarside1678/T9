// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Iron_PickAxe.h"

AItem_Iron_PickAxe::AItem_Iron_PickAxe() {
	Modifiers = {30, 1, 50, 1, 50, 1};
	ItemSocket = MainHand;
	ItemName = "Iron Pickaxe";
	ItemType = Tool;
	ItemSubType = PickAxe;
	ItemRarity = Rare;
	static ConstructorHelpers::FObjectFinder<UTexture2D> Sprite(TEXT("Texture2D'/Game/Assets/CraftResourcesIcons/Textures/Tex_tools_07.Tex_tools_07'"));
	if (Sprite.Succeeded()) {
		ItemImage = Sprite.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Meshes/Tools/Pickaxe.Pickaxe'"));
	if (Mesh.Succeeded()) {
		ItemMesh->SetWorldScale3D(FVector(0.8));
		ItemMesh->SetStaticMesh(Mesh.Object);
		ItemMesh->SetRelativeLocation(FVector(63, -23, 0));
	}
	GoldValue = 40;
}