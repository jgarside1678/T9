// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCharacter_Boar.h"
#include "Components/CapsuleComponent.h"
#include "T9/AI/Resource_Boar_Controller.h"
#include "UObject/ConstructorHelpers.h"

AResourceCharacter_Boar::AResourceCharacter_Boar() {
	Health = 100;
	MaxResourceAmount = 1000;
	CurrentResourceAmount = MaxResourceAmount;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Assets/StylizedWildAnimals/Meshes/Boar/SK_Boar.SK_Boar'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Assets/StylizedWildAnimals/Animations/Boar/BoarAnimation_BP.BoarAnimation_BP_C'"));
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/Assets/Goblin/Goblin_Attack_Montage.Goblin_Attack_Montage'"));

	if (MeshAsset.Succeeded()) {
		GetMesh()->SkeletalMesh = MeshAsset.Object;
		float Height = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -Height));
		GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
		if (AnimationAsset.Succeeded()) {
			GetMesh()->AnimClass = AnimationAsset.Class;
		}
	//	if (AnimationMont.Succeeded()) {
	//		AttackMontage = AnimationMont.Object;
	//	}
	}

	AIControllerClass = AResource_Boar_Controller::StaticClass();
}