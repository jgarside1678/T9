// Fill out your copyright notice in the Description page of Project Settings.


#include "Alliance_Champion.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"

AAlliance_Champion::AAlliance_Champion() {

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Assets/Goblin/Goblin_Animation.Goblin_Animation_C'"));
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimationMont(TEXT("AnimMontage'/Game/Assets/Goblin/Goblin_Attack_Montage.Goblin_Attack_Montage'"));
	//if (MeshAsset.Succeeded()) {
	//	GetMesh()->SkeletalMesh = MeshAsset.Object;
	//	float Height = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	//	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -Height));
	//	GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
	//	if (AnimationAsset.Succeeded()) {
	//		GetMesh()->AnimClass = AnimationAsset.Class;
	//	}
	//	if (AnimationMont.Succeeded()) {
	//		AttackMontage = AnimationMont.Object;
	//	}
	//}

	//AIControllerClass = ANPC_Defender_Controller::StaticClass();
}