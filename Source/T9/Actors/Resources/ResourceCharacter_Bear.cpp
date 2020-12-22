// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCharacter_Bear.h"
#include "Components/CapsuleComponent.h"
#include "T9/AI/Resource_Bear_Controller.h"
#include "Materials/MaterialInstance.h"
#include "UObject/ConstructorHelpers.h"

AResourceCharacter_Bear::AResourceCharacter_Bear() {
	//Base Damage, Attack Speed, AttackRange, MaxHealth, Armour, KillXP, KillGold
	Levels.Add(1, FCharacterLevels{ 5, 160, 0, 500, 5, 3, 0 });
	DecayDuration = 90;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Units/Neutral/StylizedWildAnimals/Meshes/Bear/SK_Bear.SK_Bear'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Neutral/StylizedWildAnimals/Animations/Bear/BearAnimation_BP.BearAnimation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material1(TEXT("MaterialInstanceConstant'/Game/Units/Neutral/StylizedWildAnimals/Materials/Instances/Bear/MI_Bear_Black.MI_Bear_Black'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material2(TEXT("MaterialInstanceConstant'/Game/Units/Neutral/StylizedWildAnimals/Materials/Instances/Bear/MI_Bear_Brown.MI_Bear_Brown'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material3(TEXT("MaterialInstanceConstant'/Game/Units/Neutral/StylizedWildAnimals/Materials/Instances/Bear/MI_Bear_White.MI_Bear_White'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/Units/Neutral/StylizedWildAnimals/Animations/Bear/Bear_Attack_Montage.Bear_Attack_Montage'"));
	if (Material1.Succeeded()) Materials.Add(Material1.Object);
	if (Material2.Succeeded()) Materials.Add(Material2.Object);
	if (Material3.Succeeded()) Materials.Add(Material3.Object);
	if (MeshAsset.Succeeded()) {
		GetMesh()->SkeletalMesh = MeshAsset.Object;
		if (AnimationAsset.Succeeded()) {
			GetMesh()->AnimClass = AnimationAsset.Class;
		}
		if (Materials.Num() > 0) GetMesh()->SetMaterial(0, Materials[FMath::RandRange(0, Materials.Num() - 1)]);
		if (AnimationMont.Succeeded()) {
			AttackMontage = AnimationMont.Object;
		}
	}
	CapsuleRadius = 100;

	AIControllerClass = AResource_Bear_Controller::StaticClass();
}
