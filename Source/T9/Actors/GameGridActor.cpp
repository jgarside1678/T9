// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGridActor.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "T9/Actors/Buildings/BuildingActor.h"
#include "ProceduralMeshComponent.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "T9/Actors/Resources/Resource_Wood.h"
#include "T9/Actors/Resources/Resource_Stone.h"
#include "T9/Actors/Resources/Resource_Food.h"
#include "DrawDebugHelpers.h"
#include "Internationalization/Text.h"


// Sets default values
AGameGridActor::AGameGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->SetActorHiddenInGame(true);
	PrimaryActorTick.bCanEverTick = true;
	if (Vertices.Num() > 0) Vertices.Empty();
	LineMesh = CreateDefaultSubobject< UProceduralMeshComponent>(TEXT("Line Mesh"));
	RootComponent = LineMesh;
	SelectionMeshRotationPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Selection Mesh Pivot"));
	SelectionMeshRotationPivot->SetupAttachment(LineMesh);

	SelectionMesh = CreateDefaultSubobject< UProceduralMeshComponent>(TEXT("Selection Mesh"));
	SelectionMesh->SetupAttachment(SelectionMeshRotationPivot);
	SelectionMesh->SetVisibleFlag(false);

	LineColour = CreateDefaultSubobject<UMaterialInstance>(TEXT("GridColour Material"));
	SelectionColour = CreateDefaultSubobject<UMaterialInstance>(TEXT("GridSelectionColour Material"));


	static ConstructorHelpers::FObjectFinder<UMaterialInstance> LineC(TEXT("MaterialInstanceConstant'/Game/Materials/Grid/GridColour_Line.GridColour_Line'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SelectionC(TEXT("MaterialInstanceConstant'/Game/Materials/Grid/GridColour_Selection.GridColour_Selection'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> PreviewMat(TEXT("Material'/Game/Materials/Grid/GridColour_Preview.GridColour_Preview'"));

	if (LineC.Succeeded()) {
		LineColour = LineC.Object;
		LineMesh->SetMaterial(0,LineColour);
	}
	if (SelectionC.Succeeded()) {
		SelectionColour = SelectionC.Object;
		SelectionMesh->SetMaterial(0, SelectionColour);
	}
	if (PreviewMat.Succeeded()) {
		PreviewMaterial = PreviewMat.Object;
	}

	//LineMesh creating lines
	for (int x = 0; x <= NumberOfRows; x++) {
		float LineStart = x * TileSize;
		float LineEnd = GridWidth();
		CreateGeometry(FVector(LineStart, 0.0f, 0.0f), FVector(LineStart, LineEnd, 0.0f), LineThickness, Vertices, Triangles);
	}
	for (int x = 0; x <= NumberOfColumns; x++) {
		float LineStart = x * TileSize;
		float LineEnd = GridHeight();
		CreateGeometry(FVector(0.0f, LineStart, 0.0f), FVector(LineEnd, LineStart, 0.0f), LineThickness, Vertices, Triangles);
	}

	//LineMesh Rendering
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
	UV0.Init(FVector2D(0.0f, 0.0f), Vertices.Num());
	Normals.Init(FVector(0.0f, 0.0f, 1.0f), Vertices.Num());
	VertexColors.Init(FColor(0.0f, 0.0f, 0.0f, 1.0f), Vertices.Num());
	Tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), Vertices.Num());

	LineMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, false);


	//SectionMesh Rendering
	Normals.Empty();
	UV0.Empty();
	VertexColors.Empty();
	Tangents.Empty();
	UV0.Init(FVector2D(0.0f, 0.0f), SelectionVertices.Num());
	Normals.Init(FVector(0.0f, 0.0f, 1.0f), SelectionVertices.Num());
	VertexColors.Init(FColor(0.0f, 0.0f, 0.0f, 1.0f), SelectionVertices.Num());
	Tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), SelectionVertices.Num());
	CreateGeometry(FVector(0.0f, (TileSize / 2), 0.0f), FVector(TileSize, (TileSize / 2), 0.0f), TileSize, SelectionVertices, SelectionTriangles);
	SelectionMesh->CreateMeshSection(0, SelectionVertices, SelectionTriangles, Normals, UV0, VertexColors, Tangents, false);

}

// Called when the game starts or when spawned
void AGameGridActor::BeginPlay()
{
	Super::BeginPlay();
	ScaleSelectionTile(1, 1);
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	GenerateTerrain();
}

// Called every frame
void AGameGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameGridActor::CreateGeometry(FVector Start, FVector End, float Thickness, TArray<FVector>& Vert, TArray<int>& Tria)
{
	FVector Diff = End - Start;
	Diff.Normalize();
	FVector ThicknessDirection = FVector::CrossProduct(Diff, FVector(0.0f, 0.0f, 1.0f));
	Tria.Add(2 + Vert.Num());
	Tria.Add(1 + Vert.Num());
	Tria.Add(0 + Vert.Num());
	Tria.Add(2 + Vert.Num());
	Tria.Add(3 + Vert.Num());
	Tria.Add(1 + Vert.Num());
	FVector Temp = ThicknessDirection * (Thickness / 2);
	Vert.Add(Start + Temp);
	Vert.Add(End + Temp);
	Vert.Add(Start - Temp);
	Vert.Add(End - Temp);
}

float AGameGridActor::GridWidth()
{
	return (NumberOfColumns * TileSize);
}

float AGameGridActor::GridHeight()
{
	return (NumberOfRows * TileSize);
}



//GridSelection and Building


bool AGameGridActor::LocationToTile(const FVector &Location)
{

	//Positions Mouse based On Selection Size
	if(SelectionLengthX % 2 == 0 && SelectionLengthX > 1)	CurrentRow = round(((Location.X - GetActorLocation().X) / GridWidth()) * NumberOfRows);
	else CurrentRow = floor(((Location.X - GetActorLocation().X) / GridWidth()) * NumberOfRows);
	if (SelectionLengthX % 2 == 0 && SelectionLengthY > 1)  CurrentColumn = round(((Location.Y - GetActorLocation().Y) / GridHeight()) * NumberOfColumns);
	else CurrentColumn = floor(((Location.Y - GetActorLocation().Y) / GridHeight()) * NumberOfColumns);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentRow);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentColumn);
	if (((CurrentRow >= 0) && (CurrentRow < NumberOfRows)) && (CurrentColumn >= 0) && (CurrentColumn < NumberOfColumns)) return true;
	else return false;
}


bool AGameGridActor::TileToGridLocation()
{
	if (((CurrentRow >= 0) && (CurrentRow < NumberOfRows)) && (CurrentColumn >= 0) && (CurrentColumn < NumberOfColumns)) {
		float TempX = CurrentRow * TileSize + GetActorLocation().X;
		float TempY = CurrentColumn * TileSize + GetActorLocation().Y;
		int TilesWidth = SelectionLengthY;
		int TilesHeight = SelectionLengthX;
		if ((SelectionRotationY % 180) != 0) Swap(TilesWidth, TilesHeight);
		if (SelectionLengthY > 1) {
			TempY -= floor(TilesWidth * 0.5) * TileSize;
		}
		if (SelectionLengthX > 1) {
			TempX -= floor(TilesHeight * 0.5) * TileSize;
		}
		//DrawDebugLine(GetWorld(), FVector(TempX, TempY, 0), FVector(TempX, TempY, GetActorLocation().Z + 1000), FColor::Red, false);
		SelectedGridLocation = FVector(TempX, TempY, 0);
		SelectionGridPivotLocation = FVector(TempX + (TilesHeight * TileSize / 2), TempY + (TilesWidth * TileSize / 2), GetActorLocation().Z);
		return true;
	}
	return false;
}


void AGameGridActor::SetSelectedTile()
{
	bool IsValid = TileToGridLocation();
	if (IsValid) {
		SelectionMesh->SetMeshSectionVisible(0, true);
		SelectionMeshRotationPivot->SetWorldLocation(SelectionGridPivotLocation);
		SelectionMesh->SetRelativeLocation(FVector((SelectionLengthX * 0.5 * -TileSize), (SelectionLengthY * 0.5 * -TileSize) , 0));
		MovePreviewObject(SelectionGridPivotLocation);
		//DrawDebugLine(GetWorld(), SelectionGridPivotLocation, FVector(SelectionGridPivotLocation.X, SelectionGridPivotLocation.Y, GetActorLocation().Z + 1000), FColor::Red, false);
	}
	else {
		SelectionMesh->SetMeshSectionVisible(0, false);
	}
}


void AGameGridActor::SetTilesActive(FVector Location, int TilesWidth, int TilesHeight)
{
	if ((SelectionRotationY % 180) != 0) Swap(TilesWidth, TilesHeight);
	int Row = round(((Location.X - GetActorLocation().X) / GridWidth()) * NumberOfRows);
	int Column = round(((Location.Y - GetActorLocation().Y) / GridHeight()) * NumberOfColumns);
	for (int x = 0; x < TilesHeight; x++) {
		for (int y = 0; y < TilesWidth; y++) {
			if (((Row + x) >= 0 && (Row + x) <= NumberOfRows) && ((Column + y) >= 0 && (Column + y) <= NumberOfColumns)) {
				IsGridSlotUsed[Row + x][Column + y] = true;
			}
		}
	}
	//DrawDebugBox(GetWorld(), (SelectionGridPivotLocation), (FVector(TilesHeight * TileSize * 0.5, TilesWidth * TileSize * 0.5, 100)), FColor::Green, true, -1, 0, 10);
}

void AGameGridActor::SetTilesUnactive(FVector Location, int TilesWidth, int TilesHeight, int Rot)
{
	if ((Rot % 180) == 0) Swap(TilesWidth, TilesHeight);
	int Row = round(((Location.X - GetActorLocation().X) / GridWidth()) * NumberOfRows);
	int Column = round(((Location.Y - GetActorLocation().Y) / GridHeight()) * NumberOfColumns);
	for (int x = 0; x <= TilesHeight; x++) {
		for (int y = 0; y <= TilesWidth; y++) {
			if (((Row + x) >= 0 && (Row + x) <= NumberOfRows) && ((Column + y) >= 0 && (Column + y) <= NumberOfColumns)) {
				IsGridSlotUsed[Row + x][Column + y] = false;
			}
		}
	}
}


//Check if tiles are active in the 2D array
bool AGameGridActor::CheckGridLocation(FVector CheckLocation, int BuildingWidth, int BuildingHeight)
{
    //DrawDebugLine(GetWorld(), CheckLocation, FVector(CheckLocation.X, CheckLocation.Y, 1000), FColor::Red, true, 20, 10, 5);
	if ((SelectionRotationY % 180) != 0) Swap(BuildingWidth, BuildingHeight);
	int Row = round(((CheckLocation.X - GetActorLocation().X) / GridWidth()) * NumberOfRows);
	int Column = round(((CheckLocation.Y - GetActorLocation().Y) / GridHeight()) * NumberOfColumns);
	for (int x = 0; x < BuildingHeight; x++) {
		for (int y = 0; y < BuildingWidth; y++) {
			if (((Row + x) >= 0 && (Row + x) <= NumberOfRows-1) && ((Column + y) >= 0 && (Column + y) <= NumberOfColumns-1)) {
				if (IsGridSlotUsed[Row + x][Column + y] == true) return false;
			}
			else return false;
		}
	}
	//DrawDebugBox(GetWorld(), (SelectionGridPivotLocation), (FVector(BuildingHeight * TileSize * 0.5, BuildingWidth * TileSize * 0.5, 100)), FColor::Yellow, true, -1, 0, 10);
	return true;
}

//Method for Building ABuildingActor children
ABuildingActor* AGameGridActor::BuildBuildingOnTile(FBuildingMenuSlot ObjectToBuild) {
	FVector Location = SelectionGridPivotLocation;
	if (CheckGridLocation(SelectedGridLocation, SelectionLengthY, SelectionLengthX)) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = false;
		ABuildingActor* SpawnedActorRef = GetWorld()->SpawnActor<ABuildingActor>(ObjectToBuild.Building, Location, FRotator(0.0f, SelectionRotationY, 0.0f), SpawnParams);
		if (SpawnedActorRef) {
			UE_LOG(LogTemp, Warning, TEXT("Object Spawned"));
			//BuiltBuildings.Add(SpawnedActorRef);
			SetTilesActive(SelectedGridLocation, SelectionLengthY, SelectionLengthX);
			SpawnedActorRef->BuildingInit(this, SelectionGridPivotLocation, SelectedGridLocation, SelectionRotationY);
			OnBuildingConstructed.Broadcast();
			if (PS) {
				if (PS->GetBuildingStorageCount(SpawnedActorRef->GetName()) <= 0) {
					PS->RemoveResources(SpawnedActorRef->GetCost());
					PS->AddCurrentXP(SpawnedActorRef->GetBuildXP());
				}
				else {
					PS->SetBuildingStorageCount(SpawnedActorRef->GetName(), PS->GetBuildingStorageCount(SpawnedActorRef->GetName()) - 1);
				}
			}
			return SpawnedActorRef;
		}
		else return nullptr;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Object Not spawned because an object is already present on this tile location."));
		return nullptr;
	}
}


//Toggles selection tile on and off as well as preview building
void AGameGridActor::ToggleSelectionTile(bool Toggle)
{

	if(SelectionMesh) SelectionMesh->SetVisibility(Toggle);
	if (PreviewBuilding) PreviewBuilding->SetActorHiddenInGame(!Toggle);

}

//Scales selection tile to same size as preview building
void AGameGridActor::ScaleSelectionTile(int ScaleX, int ScaleY)
{
	SelectionMesh->SetWorldScale3D(FVector(ScaleX, ScaleY, 1));
	SelectionLengthX = ScaleX;
	SelectionLengthY = ScaleY;
}

//Creates a preview building for building menu
AActor* AGameGridActor::CreatePreviewObject(FBuildingMenuSlot ObjectToBuild)
{
	if (ObjectToBuild.Building != nullptr) {
		FVector Location = SelectionGridPivotLocation;
		FActorSpawnParameters SpawnParams;
		SpawnParams.bDeferConstruction = true;
		PreviewBuilding = GetWorld()->SpawnActor<AActor>(ObjectToBuild.Building, Location, FRotator(0.0f, SelectionRotationY, 0.0f), SpawnParams);
		PreviewBuilding->SetActorEnableCollision(false);
		PreviewBuilding->SetActorTickEnabled(false);
		UPrimitiveComponent* PrimitiveComponent = PreviewBuilding->FindComponentByClass < UPrimitiveComponent>();
		PrimitiveComponent->SetCollisionProfileName("NoCollision");
		TArray<UActorComponent*> Components = PreviewBuilding->GetComponentsByClass(UStaticMeshComponent::StaticClass());
		for (int x = 0; x < Components.Num(); x++) {
			UStaticMeshComponent* Mesh = (UStaticMeshComponent*)Components[x];
			if (Mesh) {
				for (int z = 0; z < Mesh->GetMaterials().Num(); z++) {
					Mesh->SetMaterial(z, PreviewMaterial);
				}
				Mesh->SetTranslucentSortPriority(-100);
			}
		}
		return PreviewBuilding;
	}
	return nullptr;
}

//Moves the preview building
void AGameGridActor::MovePreviewObject(FVector Location)
{
	if (PreviewBuilding) {
		PreviewBuilding->SetActorLocation(Location);
		PreviewBuilding->SetActorRotation(FRotator(0.0f, SelectionRotationY, 0.0f));
	}

}

//Rotates the preview building
void AGameGridActor::RotatePreviewObject(int amount)
{
	if (PreviewBuilding) {
		SelectionRotationY += amount;
		PreviewBuilding->SetActorRotation(FRotator(0.0f, SelectionRotationY, 0.0f));
		SelectionMeshRotationPivot->SetRelativeRotation(FRotator(0.0f, SelectionRotationY, 0.0f));
	}
}

bool AGameGridActor::DestroyPreviewObject()
{
	if (PreviewBuilding) {
		PreviewBuilding->Destroy();
		PreviewBuilding = nullptr;
	}
	return false;
}


static void GetRandomSections(TArray<FVector2D>& Sections) {
	Sections.Empty();
	Sections.Add(FVector2D(FMath::RandRange(10, 90), FMath::RandRange(10, 80)));
	Sections.Add(FVector2D(FMath::RandRange(90, 180), FMath::RandRange(10, 90)));
	Sections.Add(FVector2D(FMath::RandRange(10, 90), FMath::RandRange(90, 180)));
	Sections.Add(FVector2D(FMath::RandRange(90, 180), FMath::RandRange(90, 180)));
}


void AGameGridActor::GenerateTerrain() {
	TArray<FVector2D> Sections;
	GetRandomSections(Sections);

	for (int x = 0; x < Sections.Num(); x++) {
		AResourceActor* WoodResource;
		FActorSpawnParameters SpawnParams;
		float XPosition = (Sections[x].X *100) +GetActorLocation().X;
		float YPosition = (Sections[x].Y * 100) + GetActorLocation().Y;
		WoodResource = GetWorld()->SpawnActor<AResourceActor>(AResource_Wood::StaticClass(), FVector(XPosition, YPosition, 5.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		WoodResource->ResourceInit(this, (Tiers)FMath::RandRange(0, 2));
	}

	GetRandomSections(Sections);
	for (int x = 0; x < Sections.Num(); x++) {
		AResourceActor* StoneResource;
		FActorSpawnParameters SpawnParams;
		float XPosition = (Sections[x].X * 100) + GetActorLocation().X;
		float YPosition = (Sections[x].Y * 100) + GetActorLocation().Y;
		StoneResource = GetWorld()->SpawnActor<AResourceActor>(AResource_Stone::StaticClass(), FVector(XPosition, YPosition, 5.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		StoneResource->ResourceInit(this, (Tiers)FMath::RandRange(0, 2));
	}

	GetRandomSections(Sections);
	for (int x = 0; x < Sections.Num(); x++) {
		AResourceActor* FoodResource;
		FActorSpawnParameters SpawnParams;
		float XPosition = (Sections[x].X * 100) + GetActorLocation().X;
		float YPosition = (Sections[x].Y * 100) + GetActorLocation().Y;
		FoodResource = GetWorld()->SpawnActor<AResourceActor>(AResource_Food::StaticClass(), FVector(XPosition, YPosition, 5.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		FoodResource->ResourceInit(this, (Tiers)FMath::RandRange(0, 2));
	}

}

void AGameGridActor::ToggleGridSpaces(bool Input) {


	for (int x = 0; x < PS->SpawnedBuildings.Num(); x++) {
		if (PS->SpawnedBuildings[x] && PS->SpawnedBuildings[x]->GridSpace) PS->SpawnedBuildings[x]->GridSpace->SetVisibility(Input);
	}
	for (int x = 0; x < PS->SpawnedResources.Num(); x++) {
		if (PS->SpawnedResources[x] && PS->SpawnedResources[x]->GridSpace) PS->SpawnedResources[x]->GridSpace->SetVisibility(Input);
	}
}

