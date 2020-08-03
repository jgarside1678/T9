// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Wooden_Pickaxe.h"

AItem_Wooden_Pickaxe::AItem_Wooden_Pickaxe() {
	ItemName = "Wooden Pickaxe";
	ItemRarity = Rare;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Meshes/Tools/Pickaxe.Pickaxe'"));
	if (Mesh.Succeeded()) {
		ItemMesh->SetWorldScale3D(FVector(0.7));
		ItemMesh->SetStaticMesh(Mesh.Object);
		ItemMesh->SetRelativeLocation(FVector(63, -23, 0));
	}
	GoldValue = 10;
}