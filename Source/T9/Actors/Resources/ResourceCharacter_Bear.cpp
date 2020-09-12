// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCharacter_Bear.h"
#include "Components/CapsuleComponent.h"
#include "T9/AI/Resource_Bear_Controller.h"
#include "Materials/MaterialInstance.h"
#include "UObject/ConstructorHelpers.h"

AResourceCharacter_Bear::AResourceCharacter_Bear() {
	Health = 500;
	MaxResourceAmount = 5000;
	CurrentResourceAmount = MaxResourceAmount;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AI/Neutral/StylizedWildAnimals/Meshes/Bear/SK_Bear.SK_Bear'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/AI/Neutral/StylizedWildAnimals/Animations/Bear/BearAnimation_BP.BearAnimation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material1(TEXT("MaterialInstanceConstant'/Game/AI/Neutral/StylizedWildAnimals/Materials/Instances/Bear/MI_Bear_Black.MI_Bear_Black'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material2(TEXT("MaterialInstanceConstant'/Game/AI/Neutral/StylizedWildAnimals/Materials/Instances/Bear/MI_Bear_Brown.MI_Bear_Brown'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material3(TEXT("MaterialInstanceConstant'/Game/AI/Neutral/StylizedWildAnimals/Materials/Instances/Bear/MI_Bear_White.MI_Bear_White'"));
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/Assets/Goblin/Goblin_Attack_Montage.Goblin_Attack_Montage'"));
	if (Material1.Succeeded()) Materials.Add(Material1.Object);
	if (Material2.Succeeded()) Materials.Add(Material2.Object);
	if (Material3.Succeeded()) Materials.Add(Material3.Object);
	if (MeshAsset.Succeeded()) {
		GetMesh()->SkeletalMesh = MeshAsset.Object;
		float Height = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -Height));
		GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
		if (AnimationAsset.Succeeded()) {
			GetMesh()->AnimClass = AnimationAsset.Class;
		}
		if (Materials.Num() > 0) GetMesh()->SetMaterial(0, Materials[FMath::RandRange(0, Materials.Num() - 1)]);
		//	if (AnimationMont.Succeeded()) {
		//		AttackMontage = AnimationMont.Object;
		//	}
	}

	AIControllerClass = AResource_Bear_Controller::StaticClass();
}
