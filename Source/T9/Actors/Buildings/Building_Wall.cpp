// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_Wall.h"

ABuilding_Wall::ABuilding_Wall()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorTickInterval(1);
	HealthBarHeight = 500;
	OutlineColour = 1;
	GridLength = FVector2D(2);
	MeshDisplacement->SetRelativeLocation(FVector(-30,0, 0));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshNode(TEXT("StaticMesh'/Game/World/Pirate_Town_Set/Meshes/Wall_Join.Wall_Join'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshConnection(TEXT("StaticMesh'/Game/World/Pirate_Town_Set/Meshes/Wall_Connection.Wall_Connection'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageLevel1(TEXT("Texture2D'/Game/UI/Assets/Sprites/TownHallImage.TownHallImage'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh1(TEXT("StaticMesh'/Game/Assets/Pirate_Town_Set/Meshes/Town_Hall_2.Town_Hall_2'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh2(TEXT("StaticMesh'/Game/Assets/Tower_Defence/Models/Towers/Tower_Base1C.Tower_Base1C'"));
	//static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationMont(TEXT("AnimSequence'/Game/AI/Alliance/StylizedHumanMale/Animations/Standing_1H_Magic_Attack_01_mixamo_com.Standing_1H_Magic_Attack_01_mixamo_com'"));
	if (BaseMeshNode.Succeeded()) {
		Node = BaseMeshNode.Object;
		StaticMeshComponent->SetStaticMesh(Node);
	}
	if (BaseMeshConnection.Succeeded()) {
		Connection = BaseMeshConnection.Object;
	}
	Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 100, 1000.0f, 10.0f, ImageLevel1.Object, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{0,0, 2}, FBuildingProduction{100} });
}


void ABuilding_Wall::BuildingInit(AGameGridActor* BuildingGrid, FVector PivotLocation, FVector CornerLocation, int Rotation)
{
	Super::BuildingInit(BuildingGrid, PivotLocation, CornerLocation, Rotation);
	TArray<AActor*> OverlappedActors;
	GetOverlappingActors(OverlappedActors);
	for (int x = 0; x < OverlappedActors.Num(); x++) {
		UE_LOG(LogTemp, Warning, TEXT("REE"));
		if (ABuilding_Wall* NewNeighbour = Cast<ABuilding_Wall>(OverlappedActors[x])) {
			UE_LOG(LogTemp, Warning, TEXT("R2EE"));
			FVector NeighbourLocation = NewNeighbour->GetActorLocation();
			if (NeighbourLocation == BuildingCenterLocation + FVector(-200, 0, 0)) Top = NewNeighbour;
			else if (NeighbourLocation == BuildingCenterLocation + FVector(200, 0, 0)) Bottom = NewNeighbour;
			else if (NeighbourLocation == BuildingCenterLocation + FVector(0, -200, 0)) Right = NewNeighbour;
			else if (NeighbourLocation == BuildingCenterLocation + FVector(0, 200, 0)) Left = NewNeighbour;
			SetupWall();
		}
	}
}

int ABuilding_Wall::GetCurrentState()
{
	return (int)CurrentState;
}

// Called when the game starts or when spawned
void ABuilding_Wall::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding_Wall::SetupWall()
{
	if (Left && Right && !Top && !Bottom) {
		if (GridRotation % 90 == 0) {
			SetActorRotation(FRotator(0));
			GridRotation = 0;
		}
		StaticMeshComponent->SetStaticMesh(Connection);
		MeshDisplacement->SetRelativeLocation(FVector(-15, 8, 0));
		CurrentState = WallState::Connection;
	}
	else if (Top && Bottom && !Left && !Right) {
		if (GridRotation == 0 || GridRotation % 180 == 0) {
			SetActorRotation(FRotator(0, 90, 0));
			GridRotation = 90;
		}
		MeshDisplacement->SetRelativeLocation(FVector(-15, 8, 0));
		StaticMeshComponent->SetStaticMesh(Connection);
		CurrentState = WallState::Connection;
	}
	else {
		StaticMeshComponent->SetStaticMesh(Node);
		MeshDisplacement->SetRelativeLocation(FVector(-30, 0, 0));
		CurrentState = WallState::Node;
	}
}

void ABuilding_Wall::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABuilding_Wall* NewNeighbour = Cast<ABuilding_Wall>(OtherActor)) {
		FVector NeighbourLocation = NewNeighbour->GetActorLocation();
		if (NeighbourLocation == BuildingCenterLocation + FVector(-200, 0, 0)) Top = NewNeighbour;
		else if (NeighbourLocation == BuildingCenterLocation + FVector(200, 0, 0)) Bottom = NewNeighbour;
		else if (NeighbourLocation == BuildingCenterLocation + FVector(0, -200, 0)) Right = NewNeighbour;
		else if (NeighbourLocation == BuildingCenterLocation + FVector(0, 200, 0)) Left = NewNeighbour;
		SetupWall();
	}
}

void ABuilding_Wall::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABuilding_Wall* OldNeighbour = Cast<ABuilding_Wall>(OtherActor)) {
		FVector NeighbourLocation = OldNeighbour->GetActorLocation();
		if (NeighbourLocation == BuildingCenterLocation + FVector(-200, 0, 0)) Top = nullptr;
		else if (NeighbourLocation == BuildingCenterLocation + FVector(200, 0, 0)) Bottom = nullptr;
		else if (NeighbourLocation == BuildingCenterLocation + FVector(0, -200, 0)) Right = nullptr;
		else if (NeighbourLocation == BuildingCenterLocation + FVector(0, 200, 0)) Left = nullptr;
		SetupWall();
	}
}
