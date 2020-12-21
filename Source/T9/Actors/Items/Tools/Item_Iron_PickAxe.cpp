// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Iron_PickAxe.h"

AItem_Iron_PickAxe::AItem_Iron_PickAxe() {
	Modifiers = { FItemModifiersOffensive{50, 1.2}, FItemModifiersDefensive{}, FItemModifiersProduction{30, 1} };
	ItemSocket = MainHand;
	ItemName = "Iron PickAxe";
	ItemType = Tool;
	ItemSubType = Axe;
	ItemRarity = Rare;
	ItemEquipedTransform = FTransform(FRotator(76.811546, -275.199890, -35.352055), FVector(-9.757370, 15.685856, -2.384092), FVector(0.4));// (Pitch = 62.345627, Yaw = 183.599503, Roll = 58.273315)
	ItemSheathedTransform = FTransform(FRotator(0.000000, 269.999237, 53.999889), FVector(-44.610828, 18.124989,-22.864485), FVector(0.4));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Sprite(TEXT("Texture2D'/Game/UI/Assets/Sprites/IronTwoHandedHammerImage.IronTwoHandedHammerImage'"));
	if (Sprite.Succeeded()) {
		ItemImage = Sprite.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/World/StylizedWeaponKIt/Weapons/Models/SM_BattleHammer.SM_BattleHammer'"));
	if (Mesh.Succeeded()) {
		ItemMesh->SetWorldScale3D(FVector(0.5));
		ItemMesh->SetStaticMesh(Mesh.Object);
		ItemMesh->SetRelativeLocation(FVector(0,-50,0));
		ItemMesh->SetRelativeRotation(FRotator(90.000000, -23, 90.000000));
	}
	GoldValue = 40;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MaleAttackMontage(TEXT("AnimMontage'/Game/Units/Alliance/StylizedHumanMale/Animations/HumanMale_Attack_2Handed_Overhead_Montage.HumanMale_Attack_2Handed_Overhead_Montage'"));
	if (MaleAttackMontage.Succeeded()) ItemAnimations.Add(HumanMale, MaleAttackMontage.Object);
}