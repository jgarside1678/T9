// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingActor.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/UObjectGlobals.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/MainPlayerController.h"
#include "T9/MainPlayerState.h"
#include "T9/Actors/Items/ItemActor.h"
#include "T9/Actors/Components/InventoryComponent.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "T9/Characters/Alliance/AllianceCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "T9/Actors/GameGridActor.h"
#include "Components/AudioComponent.h"
#include "T9/T9GameModeBase.h"
#include "T9/Widgets/HealthBarWidget.h"
#include "Components/WidgetComponent.h"
#include "T9/Widgets/QuickSelectMenu.h"

#include "InstancedFoliageActor.h"
#include "FoliageType.h"
// Sets default values
ABuildingActor::ABuildingActor() : 
	HealthWidgetComponent(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"))),
	QuickSelectWidgetComponent(CreateDefaultSubobject<UWidgetComponent>(TEXT("Quick Select")))
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(0.025);
	BuildingRangeCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DefenceRangeCollider"));
	BuildingRangeCollider->SetCollisionProfileName("Trigger");
	BuildingRangeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	BuildingRangeCollider->SetCanEverAffectNavigation(false);
	RootComponent = BuildingRangeCollider;
	//Needed Because all the meshs are made for a right handed cartesian graph ffs.
	MeshDisplacement = CreateDefaultSubobject<USceneComponent>(TEXT("MeshDisplacement"));
	MeshDisplacement->SetupAttachment(RootComponent);
	MeshDisplacement->SetRelativeRotation(FRotator(0, -90, 0));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(MeshDisplacement);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	if (StaticMeshComponent) {
		StaticMeshComponent->SetCustomDepthStencilValue(OutlineColour);
		StaticMeshComponent->SetRenderCustomDepth(false);
		StaticMeshComponent->SetGenerateOverlapEvents(true);
	}
	GridSpace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridSpace"));
	GridSpace->SetCanEverAffectNavigation(false);
	GridSpace->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GridSpace->SetupAttachment(RootComponent);
	if (GridSpace) {
		GridSpace->SetCustomDepthStencilValue(OutlineColour);
		GridSpace->SetRenderCustomDepth(true);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Plane(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> PlaneColour(TEXT("MaterialInstanceConstant'/Game/Materials/Grid/GridSpace_Buildings.GridSpace_Buildings'"));
		if (Plane.Succeeded()) {
			GridSpace->SetStaticMesh(Plane.Object);
			GridSpace->SetMaterial(0, PlaneColour.Object);
		}
	}

	//static ConstructorHelpers::FObjectFinder<USoundBase> UpgradeSound(TEXT("SoundCue'/Game/Ultimate_SFX_Bundle/Pirate_Sounds_Pro/Cues/Reparing_ship/Reparing_ship_6_Cue.Reparing_ship_6_Cue'"));
 //   UpgradeAudio = UGameplayStatics::SpawnSound2D(this, UpgradeSound.Object, 0.2);
	//if(UpgradeAudio) UpgradeAudio->SetActive(false);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	InventoryComponent->SetCapacity(3);

	InventoryComponent->AddInventorySlot(FSlot{});
	InventoryComponent->AddInventorySlot(FSlot{});
	InventoryComponent->AddInventorySlot(FSlot{});
	InventoryComponent->OnInventoryUpdate.AddDynamic(this, &ABuildingActor::UpdateBuildingModifiers);

	//Widgets

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthWidget(TEXT("WidgetBlueprint'/Game/UI/AllianceHealthBar.AllianceHealthBar_C'"));
	if (HealthWidget.Succeeded()) HealthWidgetClass = HealthWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> QuickSelectWidget(TEXT("WidgetBlueprint'/Game/UI/QuickSelectMenu_BP.QuickSelectMenu_BP_C'"));
	if (QuickSelectWidget.Succeeded()) QuickSelectWidgetClass = QuickSelectWidget.Class;

	if (HealthWidgetComponent) {
		HealthWidgetComponent->SetupAttachment(RootComponent);
		HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		if (HealthWidgetClass != nullptr) HealthWidgetComponent->SetWidgetClass(HealthWidgetClass);
		HealthBar = Cast<UHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
		HealthWidgetComponent->SetVisibility(false);
	}

	if (QuickSelectWidgetComponent) {
		QuickSelectWidgetComponent->SetupAttachment(RootComponent);
		QuickSelectWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		QuickSelectWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, QuickSelectWidgetHeight));
		QuickSelectWidgetComponent->SetVisibility(false);
		if (QuickSelectWidgetClass != nullptr) QuickSelectWidgetComponent->SetWidgetClass(QuickSelectWidgetClass);
	}

}


// Called when the game starts or when spawned
void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	if (Upgrades.Num() == 0) Upgrades.Add(1, FBuildingUpgrades{ 100.0f, 100 ,100.0f, 0.0f, nullptr, FBuildingCosts{100, 10, 10, 10}, FBuildingAttack{}, FBuildingProduction{0} });
	if (StaticMeshComponent->GetStaticMesh()) {
		BuildingDetectionRange = Upgrades[Level].Attack.AttackRangeMultipler;
		BuildingExtent = StaticMeshComponent->GetStaticMesh()->GetBoundingBox().GetExtent() * StaticMeshComponent->GetRelativeScale3D();
		BuildingRangeCollider->SetBoxExtent(BuildingExtent * BuildingDetectionRange);
		BuildingRangeCollider->OnComponentBeginOverlap.AddDynamic(this, &ABuildingActor::BeginOverlap);
		BuildingRangeCollider->OnComponentEndOverlap.AddDynamic(this, &ABuildingActor::EndOverlap);
		BuildingRangeCollider->ShapeColor = FColor::White;

		//DrawDebugBox(GetWorld(), GetActorLocation(), BuildingExtent, FQuat(GetActorRotation()), FColor::Red, true, -1, 0, 10);
		//DrawDebugBox(GetWorld(), GetActorLocation(), (BuildingRangeCollider->GetScaledBoxExtent()), FQuat(GetActorRotation()), FColor::Yellow, true, -1, 0, 10);
	}
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	PS->AddPower(Upgrades[Level].PowerRating);

	CalculateDamage();
	CalculateMaxHealth();
	CalculateDefence();
	CalculateAttackRange();
	CalculateAttackSpeed();

	TArray<AActor*> CollidingActors;
	GetOverlappingActors(CollidingActors, AEnemyCharacter::StaticClass());
	if(CollidingActors.Num() > 0) SetTarget();
	TotalCosts = Upgrades[Level].Cost;
	PS->SetBuildingCount(BuildingName, GetBuildingCount() + 1);
	PS->SpawnedBuildings.Add(this);
	HealthBar = Cast<UHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	HealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, HealthBarHeight));
	QuickSelectMenu = Cast<UQuickSelectMenu>(QuickSelectWidgetComponent->GetUserWidgetObject());
	if(QuickSelectMenu)	QuickSelectMenu->Init(this);
	ResetHealth();

	AInstancedFoliageActor* Instance = AInstancedFoliageActor::GetInstancedFoliageActorForCurrentLevel(GetWorld(), false);
	FBox newBox = FBox(GetActorLocation()- BuildingExtent, GetActorLocation()+ BuildingExtent);
	TArray<UInstancedStaticMeshComponent*> components;
	Instance->GetComponents<UInstancedStaticMeshComponent>(components);
	for (int z = 0; z < components.Num(); z++) {
		TArray<int32> Indexs = components[z]->GetInstancesOverlappingBox(newBox, true);
		for (int x = 0; x < Indexs.Num(); x++) {
			components[z]->RemoveInstance(Indexs[x]);
		}
	}
}

void ABuildingActor::SetTarget()
{
}

void ABuildingActor::SetMaxHealth(float Number)
{
	MaxHealth = Number;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}

void ABuildingActor::SetCurrentHealth(float Number)
{
	CurrentHealth = Number;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}

void ABuildingActor::IncreaseMaxHealth(float Number)
{
	MaxHealth += Number;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}

float ABuildingActor::GetCurrentHealth()
{
	return CurrentHealth;
}

float ABuildingActor::GetMaxHealth()
{
	return MaxHealth;
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
	if (QuickSelectWidgetComponent) QuickSelectWidgetComponent->SetVisibility(true);
	if (HealthWidgetComponent) HealthWidgetComponent->SetVisibility(true);
}


void ABuildingActor::SetUnSelected() {
	if (StaticMeshComponent) {
		StaticMeshComponent->SetRenderCustomDepth(false);
	}
	if (BuildingRangeCollider) BuildingRangeCollider->SetHiddenInGame(true);
	if (QuickSelectWidgetComponent) QuickSelectWidgetComponent->SetVisibility(false);
	if(HealthWidgetComponent) HealthWidgetComponent->SetVisibility(false);
}

void ABuildingActor::ResetHealth()
{
	CurrentHealth = MaxHealth;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}

AActor* ABuildingActor::GetTarget()
{
	return Target;
}

// Called every frame
//void ABuildingActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}



void ABuildingActor::BuildingInit(AGameGridActor* BuildingGrid, FVector PivotLocation, FVector CornerLocation, int Rotation)
{
	Grid = BuildingGrid;
	BuildingCenterLocation = PivotLocation;
	BuildingCornerLocation = CornerLocation;
	GridRotation = Rotation;
	GridSpace->SetRelativeLocation(FVector(0,0, 1));
	GridSpace->SetRelativeScale3D(FVector(GridLength.X, GridLength.Y, 1));
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

void ABuildingActor::TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage)
{
	int ScaledDamage = UKismetMathLibrary::FCeil(AmountOfDamage * DefenceDamageTakenMultiplier);
	if((!Disabled && TypeDamage == All) || (!Disabled && TypeDamage == TypeOfDamage)) {
		CurrentHealth -= ScaledDamage;
		if (CurrentHealth <= 0) {
			SetDisabled(true);
			CurrentHealth = 0;
		}
		if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
	}
}


void ABuildingActor::DamageEnemy(AActor* Actor, float AmountOfDamage)
{
}

DamageType ABuildingActor::GetDamageType()
{
	return TypeOfDamage;
}

bool ABuildingActor::IsDamageable()
{
	if (Disabled) return false;
	else return true;
}

void ABuildingActor::RemoveBuilding()
{
	UActorComponent* SpawnComp = GetComponentByClass(UBuildingSpawnComponent::StaticClass());
	if (SpawnComp) {
		((UBuildingSpawnComponent*)SpawnComp)->KillAll();
		((UBuildingSpawnComponent*)SpawnComp)->GetInventoryComponent()->SpawnAllItems();
	}
	if (Grid) Grid->SetTilesUnactive(BuildingCornerLocation, GridLength.X, GridLength.Y, GridRotation);
	IsDead = true;
	if (PS) {
		PS->AddResources(TotalCosts*0.5);
		if (!Disabled) {
			PS->AddPower(-Upgrades[Level].PowerRating);
		}
		PS->BuildingArrayClean();
		PS->SetBuildingStorageCount(BuildingName, PS->GetBuildingStorageCount(BuildingName) + 1);
		PS->SetBuildingCount(BuildingName, GetBuildingCount() - 1);
	}
	InventoryComponent->SpawnAllItems();
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
	if (Upgrades.Contains(Level+1) && PS && PS->RemoveResources(Upgrades[Level+1].Cost)) {
		Upgrading = true;
		Level++;
		TotalCosts += Upgrades[Level].Cost;

		//if (UpgradeAudio) {
		//	UpgradeAudio->SetActive(false);
		//	UpgradeAudio->SetActive(true);
		//}

		CalculateDamage();
		CalculateMaxHealth();
		CalculateDefence();
		CalculateAttackRange();
		CalculateAttackSpeed();

		if(!Disabled) PS->AddPower(Upgrades[Level].PowerRating - Upgrades[Level - 1].PowerRating);

		//Update Spawned Characters
		UActorComponent* SpawnComp = GetComponentByClass(UBuildingSpawnComponent::StaticClass());
		if (SpawnComp) ((UBuildingSpawnComponent*)SpawnComp)->UpdateSpawnedCharacters();

		if (Upgrades[Level].BaseMesh != nullptr) StaticMeshComponent->SetStaticMesh(Upgrades[Level].BaseMesh);
		PS->AddCurrentXP(Upgrades[Level].XP);
		ResetHealth();
		Upgrading = true;
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
	return Damage;
}

float ABuildingActor::GetDefence()
{
	return Defence;
}

float ABuildingActor::GetAttackRange()
{
	return AttackRange;
}

float ABuildingActor::GetAttackSpeed()
{
	return AttackSpeed;
}

UTexture2D* ABuildingActor::GetImage()
{
	if (Upgrades.Contains(Level))	return Upgrades[Level].Image;
	else return Upgrades[0].Image;
}

void ABuildingActor::RestoreBuilding()
{
	if (Disabled && PS->RemoveResources(Upgrades[Level].Cost * 0.5)) {
		ResetHealth();
		SetDisabled(false);
		if (QuickSelectMenu) QuickSelectMenu->SetUpgradeImage();
	}
}

void ABuildingActor::ToggleDisabled()
{
	SetDisabled(!Disabled);
}

void ABuildingActor::SetDisabled(bool Input)
{
	Target = nullptr;
	Disabled = Input;
	UActorComponent* SpawnComp = GetComponentByClass(UBuildingSpawnComponent::StaticClass());
	if (Disabled) {
		if (QuickSelectMenu) QuickSelectMenu->SetRestoreImage();
		if (SpawnComp) ((UBuildingSpawnComponent*)SpawnComp)->KillAll();
		PS->AddPower(-Upgrades[Level].PowerRating);
		SetActorTickEnabled(false);
	}
	else {
		SetActorTickEnabled(true);
		if (SpawnComp) ((UBuildingSpawnComponent*)SpawnComp)->Respawn();
		PS->AddPower(Upgrades[Level].PowerRating);
		SetTarget();
	}
}

bool ABuildingActor::GetDisabled()
{
	return Disabled;
}

void ABuildingActor::CalculateDamage()
{
	Damage = 0;
	if(Upgrades.Contains(Level)) Damage += Upgrades[Level].Attack.Damage;
	Damage += ItemModifiers.OffensiveStats.ItemDamageBase;
	Damage *= ItemModifiers.OffensiveStats.ItemDamageMultiplier;
}

void ABuildingActor::CalculateAttackRange()
{
	AttackRange = 0;
	if (Upgrades.Contains(Level)) AttackRange += Upgrades[Level].Attack.AttackRangeMultipler;
	AttackRange += ItemModifiers.OffensiveStats.ItemAttackRangeBase;
	AttackRange *= ItemModifiers.OffensiveStats.ItemAttackRangeMultiplier;
	BuildingRangeCollider->SetBoxExtent(BuildingExtent * AttackRange);
}

void ABuildingActor::CalculateAttackSpeed()
{
	AttackSpeed = 0;
	if (Upgrades.Contains(Level)) AttackSpeed += Upgrades[Level].Attack.AttackSpeed;
	AttackSpeed += ItemModifiers.OffensiveStats.ItemDamageBase;
	AttackSpeed *= ItemModifiers.OffensiveStats.ItemDamageMultiplier;
	AttackInterval = 10 * UKismetMathLibrary::Exp(-AttackSpeed / 100);
}

void ABuildingActor::CalculateMaxHealth()
{
	MaxHealth = 0;
	if (Upgrades.Contains(Level)) MaxHealth += Upgrades[Level].MaxHealth;
	MaxHealth += ItemModifiers.DefensiveStats.ItemHealthBase;
	MaxHealth *= ItemModifiers.DefensiveStats.ItemHealthMultiplier;
}

void ABuildingActor::CalculateDefence()
{
	Defence = 0;
	if (Upgrades.Contains(Level)) Defence += Upgrades[Level].Defence;
	Defence += ItemModifiers.DefensiveStats.ItemDefenceBase;
	Defence *= ItemModifiers.DefensiveStats.ItemDefenceMultiplier;
	DefenceDamageTakenMultiplier = UKismetMathLibrary::Exp(-Defence / 1000);
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


FBuildingUpgrades ABuildingActor::GetCurrentBaseStats() {
	return Upgrades[Level];
}

FBuildingUpgrades ABuildingActor::GetUpgradeBaseStats() {
	if (Upgrades.Contains(Level + 1))	return Upgrades[Level + 1];
	else if (Upgrades.Contains(Level))	return Upgrades[Level];
	else return FBuildingUpgrades{};
}

UInventoryComponent* ABuildingActor::GetInventory()
{
	return InventoryComponent;
}

void ABuildingActor::UpdateBuildingModifiers()
{
	UE_LOG(LogTemp, Warning, TEXT("Updated"));
	ItemModifiers = FItemModifiers();
	TArray<FSlot> Slots = InventoryComponent->GetItems();
	for (int x = 0; x < Slots.Num(); x++) {
		if (Slots[x].Item) {
			ItemModifiers += Slots[x].Item->GetItemModifiers();
			UE_LOG(LogTemp, Warning, TEXT("item stats"));
		}
	}
	CalculateDamage();
	CalculateMaxHealth();
	CalculateDefence();
	CalculateAttackRange();
	CalculateAttackSpeed();
}

UWidgetComponent* ABuildingActor::GetHealthWidget()
{
	return HealthWidgetComponent;
}

UWidgetComponent* ABuildingActor::GetQuickSelectWidget()
{
	return QuickSelectWidgetComponent;
}
