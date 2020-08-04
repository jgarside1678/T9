// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingActor.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/UObjectGlobals.h"
#include "BuildingSpawnComponent.h"
#include "MainPlayerController.h"
#include "MainPlayerState.h"
#include "EnemyCharacter.h"
#include "AllianceCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameGridActor.h"
#include "Components/AudioComponent.h"
#include "T9GameModeBase.h"

// Sets default values
ABuildingActor::ABuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(0.025);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("ParticleSystem'/Game/Particles/BuildingUpgradeParticle.BuildingUpgradeParticle'"));
	if(Particle.Succeeded()) UpgradeParticle = Particle.Object;
	BuildingRangeCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DefenceRangeCollider"));
	BuildingRangeCollider->SetCollisionProfileName("Trigger");
	BuildingRangeCollider->SetCanEverAffectNavigation(false);
	RootComponent = BuildingRangeCollider;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	if (StaticMeshComponent) {
		StaticMeshComponent->SetCustomDepthStencilValue(OutlineColour);
		StaticMeshComponent->SetRenderCustomDepth(false);
	}

	GridSpace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridSpace"));
	GridSpace->SetupAttachment(RootComponent);
	if (GridSpace) {
		GridSpace->SetCustomDepthStencilValue(OutlineColour);
		GridSpace->SetRenderCustomDepth(true);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Plane(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> PlaneColour(TEXT("MaterialInstanceConstant'/Game/Materials/Grid/GridColour_Buildings.GridColour_Buildings'"));
		if (Plane.Succeeded()) {
			GridSpace->SetStaticMesh(Plane.Object);
			GridSpace->SetMaterial(0, PlaneColour.Object);
		}
	}

	//static ConstructorHelpers::FObjectFinder<USoundBase> UpgradeSound(TEXT("SoundCue'/Game/Ultimate_SFX_Bundle/Pirate_Sounds_Pro/Cues/Reparing_ship/Reparing_ship_6_Cue.Reparing_ship_6_Cue'"));
 //   UpgradeAudio = UGameplayStatics::SpawnSound2D(this, UpgradeSound.Object, 0.2);
	//if(UpgradeAudio) UpgradeAudio->SetActive(false);

}


// Called when the game starts or when spawned
void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	if (Upgrades.Num() == 0) Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 100.0f, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{}, FBuildingProduction{0} });
	if (StaticMeshComponent->GetStaticMesh()) {
		BuildingExtent = StaticMeshComponent->GetStaticMesh()->GetBoundingBox().GetExtent();
		BuildingRangeCollider->SetBoxExtent(BuildingExtent * Upgrades[Level].Attack.AttackRangeMultipler);
		BuildingRangeCollider->OnComponentBeginOverlap.AddDynamic(this, &ABuildingActor::BeginOverlap);
		BuildingRangeCollider->OnComponentEndOverlap.AddDynamic(this, &ABuildingActor::EndOverlap);
		BuildingRangeCollider->ShapeColor = FColor::White;

		//DrawDebugBox(GetWorld(), GetActorLocation(), BuildingExtent, FQuat(GetActorRotation()), FColor::Red, true, -1, 0, 10);
		//DrawDebugBox(GetWorld(), GetActorLocation(), (BuildingRangeCollider->GetScaledBoxExtent()), FQuat(GetActorRotation()), FColor::Yellow, true, -1, 0, 10);
	}
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	ResetHealth();
	TArray<AActor*> CollidingActors;
	GetOverlappingActors(CollidingActors, AEnemyCharacter::StaticClass());
	if(CollidingActors.Num() > 0) SetTarget();
	TotalCost = Upgrades[Level].Cost.Gold;
	PS->SetBuildingCount(BuildingName, GetBuildingCount() + 1);
	PS->SpawnedBuildings.Add(this);
}

void ABuildingActor::SetTarget()
{
}

void ABuildingActor::SetMaxHealth(float Number)
{
	if (Upgrades.Contains(Level)) Upgrades[Level].MaxHealth += Number;
}

void ABuildingActor::SetCurrentHealth(float Number)
{
	CurrentHealth = Number;
}

void ABuildingActor::IncreaseMaxHealth(float Number)
{
	if (Upgrades.Contains(Level))	Upgrades[Level].Attack.Damage += Number;
}

float ABuildingActor::GetCurrentHealth()
{
	return CurrentHealth;
}

float ABuildingActor::GetMaxHealth()
{
	if (Upgrades.Contains(Level)) return Upgrades[Level].MaxHealth;
	else return 0;
}

FString ABuildingActor::GetName()
{
	return BuildingName;
}

int ABuildingActor::GetLevel()
{
	return Level;
}

void ABuildingActor::SetSelected() {
	if (StaticMeshComponent) {
		StaticMeshComponent->SetRenderCustomDepth(true);
	}
	if (BuildingRangeCollider) BuildingRangeCollider->SetHiddenInGame(false);
}


void ABuildingActor::SetUnSelected() {
	if (StaticMeshComponent) {
		StaticMeshComponent->SetRenderCustomDepth(false);
	}
	if (BuildingRangeCollider) BuildingRangeCollider->SetHiddenInGame(true);
}

void ABuildingActor::ResetHealth()
{
	if (Upgrades.Contains(Level)) CurrentHealth = Upgrades[Level].MaxHealth;
}

// Called every frame
//void ABuildingActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}



void ABuildingActor::BuildingInnit(AGameGridActor* BuildingGrid, FVector PivotLocation, FVector CornerLocation, float XLength, float YLength, int Rotation)
{
	Grid = BuildingGrid;
	BuildingCenterLocation = PivotLocation;
	BuildingCornerLocation = CornerLocation;
	GridXLength = XLength;
	GridYLength = YLength;
	GridRotation = Rotation;
	GridSpace->SetRelativeLocation(FVector(0,0, 1));
	GridSpace->SetRelativeScale3D(FVector(XLength, YLength, 1));
}

void ABuildingActor::GetBuildingRangeCollider(FVector& Origin, FVector& BoxExtent)
{
	Origin = GetActorLocation();
	BoxExtent = BuildingRangeCollider->GetScaledBoxExtent();
}

UStaticMeshComponent* ABuildingActor::GetStaticMeshComp()
{
	return StaticMeshComponent;
}

void ABuildingActor::TakeDamage(AActor* AttackingActor, float AmountOfDamage)
{
	CurrentHealth -= AmountOfDamage;
	if (CurrentHealth <= 0) {
		UActorComponent* SpawnComp = GetComponentByClass(UBuildingSpawnComponent::StaticClass());
		if (SpawnComp) ((UBuildingSpawnComponent*)SpawnComp)->KillAll();
		if (Grid) Grid->SetTilesUnactive(BuildingCornerLocation, GridXLength, GridYLength, GridRotation);
		IsDead = true;
		PS->SetBuildingCount(BuildingName, GetBuildingCount() - 1);
		PS->BuildingArrayClean();
		this->Destroy();
	}
}


void ABuildingActor::DamageEnemy(AActor* Actor, float AmountOfDamage)
{
}

void ABuildingActor::RemoveBuilding()
{
	PS->AddGold(TotalCost*0.5);
	UActorComponent* SpawnComp = GetComponentByClass(UBuildingSpawnComponent::StaticClass());
	if (SpawnComp) ((UBuildingSpawnComponent*)SpawnComp)->KillAll();
	if (Grid) Grid->SetTilesUnactive(BuildingCornerLocation, GridXLength, GridYLength, GridRotation);
	IsDead = true;
	if (PS) {
		PS->BuildingArrayClean();
		PS->SetBuildingCount(BuildingName, GetBuildingCount() - 1);
	}
	this->Destroy();
}

void ABuildingActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor)) {
		FVector Loc = Enemy->GetActorLocation();
		SetTarget();
		UE_LOG(LogTemp, Warning, TEXT("OverLap"));
	}
}


void ABuildingActor::EndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor)) {
		if (Target == OtherActor) Target = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("OverLap Ended"));
	}
}

void ABuildingActor::Upgrade() {
	if (Upgrades.Contains(Level+1) && PS->RemoveResources(Upgrades[Level].Cost)) {
		//if (UpgradeAudio) {
		//	UpgradeAudio->SetActive(false);
		//	UpgradeAudio->SetActive(true);
		//}
		Level++;

		//Update Spawned Characters
		UActorComponent* SpawnComp = GetComponentByClass(UBuildingSpawnComponent::StaticClass());
		if (SpawnComp) ((UBuildingSpawnComponent*)SpawnComp)->UpdateSpawnedCharacters();

		if(UpgradeParticle) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UpgradeParticle, GetActorLocation());
		if (Upgrades[Level].BaseMesh != nullptr) StaticMeshComponent->SetStaticMesh(Upgrades[Level].BaseMesh);
		PS->AddCurrentXP(Upgrades[Level].XP);
		BuildingRangeCollider->SetBoxExtent(BuildingExtent * Upgrades[Level].Attack.AttackRangeMultipler);
		ResetHealth();
		TotalCost += Upgrades[Level].Cost.Gold;
	}
	else UE_LOG(LogTemp, Warning, TEXT("Not enough money to upgrade"));

	UE_LOG(LogTemp, Warning, TEXT("Using Parent call"));
}

FBuildingCosts ABuildingActor::GetCost() {
	if (Upgrades.Contains(Level))	return Upgrades[Level].Cost;
	return FBuildingCosts{ 0,0,0,0 };
}

float ABuildingActor::GetBuildXP() {
	if (Upgrades.Contains(Level))	return Upgrades[Level].XP;
	else return 0;
}

float ABuildingActor::GetDamage() {
	if (Upgrades.Contains(Level))	return Upgrades[Level].Attack.Damage;
	else return 0;
}

int ABuildingActor::GetBuildingCount()
{
	if(PS->GetBuildingCount(BuildingName)) return PS->GetBuildingCount(BuildingName);
	return 0;
}

int ABuildingActor::GetMaxBuildingCount() {
	if (PS->GetMaxBuildingCount(BuildingName)) return PS->GetMaxBuildingCount(BuildingName);
	return 1;
}

