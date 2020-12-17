// Fill out your copyright notice in the Description page of Project Settings.


#include "Alliance_Wizard.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

AAlliance_Wizard::AAlliance_Wizard() {
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Body.SK_Body'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeltMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Belt.SK_Belt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BootsMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Boots.SK_Boots'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BrowsMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Brows_02.SK_Brows_02'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HairMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Hair_01.SK_Hair_01'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LowerBodyMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Pants.SK_Pants'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> UpperBodyMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Shirt.SK_Shirt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeardMesh(TEXT("SkeletalMesh'/Game/AI/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Beard_02.SK_Beard_02'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMesh(TEXT("StaticMesh'/Game/Meshes/Weapons/Pickaxe.Pickaxe'"));
	if (BodyMesh.Succeeded())MeshPeices.Add(BodyMesh.Object);
	if (BeltMesh.Succeeded())MeshPeices.Add(BeltMesh.Object);
	if (BootsMesh.Succeeded())MeshPeices.Add(BootsMesh.Object);
	if (BrowsMesh.Succeeded())MeshPeices.Add(BrowsMesh.Object);
	if (HairMesh.Succeeded())MeshPeices.Add(HairMesh.Object);
	if (LowerBodyMesh.Succeeded())MeshPeices.Add(LowerBodyMesh.Object);
	if (UpperBodyMesh.Succeeded())MeshPeices.Add(UpperBodyMesh.Object);
	if (BeardMesh.Succeeded())MeshPeices.Add(BeardMesh.Object);
	//MeshInit();
	GetMesh()->SetSkeletalMesh(MergeMeshes(FSkeletalMeshMergeParams(MeshPeices, MeshPeices[0]->Skeleton)));
	//if (ItemMesh.Succeeded()) {
	//	MainHandItemMesh->SetStaticMesh(ItemMesh.Object);
	//	MainHandItemMesh->SetRelativeScale3D(FVector(0.5));
	//	MainHandItemMesh->SetRelativeLocation(FVector(22.000000, -59.000000, 31.000000));
	//	MainHandItemMesh->SetRelativeRotation(FRotator(0, 309.599152f, 0));
	//}


	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/AI/Alliance/StylizedHumanMale/Animations/Alliance_LumberJack_AnimBP.Alliance_LumberJack_AnimBP_C'"));
	//if (AnimationAsset.Succeeded()) {
	//	GetMesh()->AnimClass = AnimationAsset.Class;
	//}
}

void AAlliance_Wizard::BeginPlay() {
	Super::BeginPlay();
}

