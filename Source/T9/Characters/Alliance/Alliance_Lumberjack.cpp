// Fill out your copyright notice in the Description page of Project Settings.


#include "Alliance_Lumberjack.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

AAlliance_Lumberjack::AAlliance_Lumberjack() {
	ResourceGatherType = Wood;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Body.SK_Body'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeltMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Belt.SK_Belt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BootsMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Boots.SK_Boots'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BrowsMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Brows_02.SK_Brows_02'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HairMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Hair_01.SK_Hair_01'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LowerBodyMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Pants.SK_Pants'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> UpperBodyMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Shirt.SK_Shirt'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BeardMesh(TEXT("SkeletalMesh'/Game/Units/Alliance/StylizedHumanMale/Meshes/ModularParts/SK_Beard_02.SK_Beard_02'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMainHandItem(TEXT("StaticMesh'/Game/Meshes/Weapons/Pickaxe.Pickaxe'"));
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
	if (DefaultMainHandItem.Succeeded()) {
		Equipment.DefaultMainHand = DefaultMainHandItem.Object;
		ResetEquipment();
	}
	GatheringLevels.Add(1, FGathererLevels{ 50, 220 });
	GatheringLevels.Add(2, FGathererLevels{ 50, 420});
	GatheringLevels.Add(3, FGathererLevels{ 50, 620});

	Levels.Add(1, FCharacterLevels{ 10, 150, 0, 100, 20 });
	Levels.Add(2, FCharacterLevels{ 20, 150, 0, 300, 50 });
	Levels.Add(3, FCharacterLevels{ 30, 150, 0, 500, 100 });

	Equipment.DefaultMainHandTransformSheathed = FTransform(FRotator(349.199066, 32.399937, 262.799347), FVector(18.000000, 20.000000, -15.000000), FVector(0.4));
	Equipment.DefaultMainHandTransformEquiped = FTransform(FRotator(-20, -30, 7), FVector(32, -40, 7), FVector(0.5));

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationAsset(TEXT("AnimBlueprint'/Game/Units/Alliance/StylizedHumanMale/Animations/AllianceLumberJackAnimation_BP.AllianceLumberJackAnimation_BP_C'"));
	if (AnimationAsset.Succeeded()) {
		GetMesh()->AnimClass = AnimationAsset.Class;
	}
}

void AAlliance_Lumberjack::BeginPlay() {
	Super::BeginPlay();
	MovementComponent->MaxWalkSpeed = 250;
}


void AAlliance_Lumberjack::SheathMainHand()
{
	Super::SheathMainHand();
	//if (MainHandItem) {
	//	MainHandItem->SetRelativeScale3D(FVector(0.4));
	//	MainHandItem->SetRelativeLocation(FVector(18.000000, 20.000000, -15.000000));
	//	MainHandItem->SetRelativeRotation(FRotator(349.199066, 32.399937, 262.799347));
	//}
}

void AAlliance_Lumberjack::EquipMainHand()
{
	Super::EquipMainHand();
	//if (MainHandItem) {
	//	MainHandItem->SetRelativeScale3D(FVector(0.5));
	//	MainHandItem->SetRelativeLocation(FVector(26.000000f, -62.000000f, 0.000000f));
	//	MainHandItem->SetRelativeRotation(FRotator(331.199005f, 313.199158f, 0));
	//}
}
