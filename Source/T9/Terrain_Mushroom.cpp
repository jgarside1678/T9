// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain_Mushroom.h"

ATerrain_Mushroom::ATerrain_Mushroom() {
	SetActorRelativeScale3D(FVector(2));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_Mushroom_Var01.SM_Mushroom_Var01'"));
	if (Mesh.Succeeded()) StaticMeshComponent->SetStaticMesh(Mesh.Object);
}


ATerrain_Mushroom1::ATerrain_Mushroom1()
{
	SetActorRelativeScale3D(FVector(4));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_Mushroom_Var02.SM_Mushroom_Var02'"));
	if (Mesh.Succeeded()) StaticMeshComponent->SetStaticMesh(Mesh.Object);
}

ATerrain_Mushroom2::ATerrain_Mushroom2()
{
	SetActorRelativeScale3D(FVector(2));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_Mushroom_Var03.SM_Mushroom_Var03'"));
	if (Mesh.Succeeded()) StaticMeshComponent->SetStaticMesh(Mesh.Object);
}

ATerrain_MushroomHabitat::ATerrain_MushroomHabitat()
{
	SetActorRelativeScale3D(FVector(2));
	StaticMeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static1MeshComponent"));
	StaticMeshComponent1->SetupAttachment(RootComponent);
	StaticMeshComponent1->SetRelativeLocation(FVector(20, 20, 0));
	StaticMeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static2MeshComponent"));
	StaticMeshComponent2->SetupAttachment(RootComponent);
	StaticMeshComponent2->SetRelativeLocation(FVector(-20, 20, 0));
	StaticMeshComponent3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static3MeshComponent"));
	StaticMeshComponent3->SetupAttachment(RootComponent);
	StaticMeshComponent3->SetRelativeLocation(FVector(0, -20, 0));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_Mushroom_Var02.SM_Mushroom_Var02'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_Mushroom_Var01.SM_Mushroom_Var01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_Mushroom_Var05.SM_Mushroom_Var05'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh4(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_Mushroom_Var06.SM_Mushroom_Var06'"));
	//if (Mesh.Succeeded()) StaticMeshComponent->SetStaticMesh(Mesh.Object);
	if (Mesh2.Succeeded()) StaticMeshComponent1->SetStaticMesh(Mesh2.Object);
	if (Mesh3.Succeeded()) StaticMeshComponent2->SetStaticMesh(Mesh3.Object);
	if (Mesh4.Succeeded()) StaticMeshComponent3->SetStaticMesh(Mesh4.Object);
	StaticMeshComponent->SetRelativeLocation(FVector(-50, 100, 0));
}
