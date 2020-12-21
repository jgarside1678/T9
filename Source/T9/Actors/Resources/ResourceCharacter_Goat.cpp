// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCharacter_Goat.h"
#include "Components/CapsuleComponent.h"
#include "T9/AI/Resource_Goat_Controller.h"
#include "Materials/MaterialInstance.h"
#include "UObject/ConstructorHelpers.h"

AResourceCharacter_Goat::AResourceCharacter_Goat() {
	Health = 100;
	DecayDuration = 30;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Units/Neutral/StylizedWildAnimals/Meshes/Goat/SK_Goat.SK_Goat'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Neutral/StylizedWildAnimals/Animations/Goat/GoatAnimation_BP.GoatAnimation_BP_C'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material1(TEXT("MaterialInstanceConstant'/Game/Units/Neutral/StylizedWildAnimals/Materials/Instances/Goat/MI_Goat_Black.MI_Goat_Black'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material2(TEXT("MaterialInstanceConstant'/Game/Units/Neutral/StylizedWildAnimals/Materials/Instances/Goat/MI_Goat_Brown.MI_Goat_Brown'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material3(TEXT("MaterialInstanceConstant'/Game/Units/Neutral/StylizedWildAnimals/Materials/Instances/Goat/MI_Goat_White.MI_Goat_White'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/Units/Neutral/StylizedWildAnimals/Animations/Goat/Goat_Idle_Montage.Goat_Idle_Montage'"));
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
		if (AnimationMont.Succeeded()) {
			AttackMontage = AnimationMont.Object;
		}
	}

	AIControllerClass = AResource_Goat_Controller::StaticClass();
}
