// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "SkeletalMeshMerge.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/SkeletalMesh.h"
#include "Components/WidgetComponent.h"
#include "T9/Widgets/HealthBarWidget.h"
#include "T9/Actors/Projectiles/Projectile.h"
#include "T9/MainPlayerState.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/MainPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "T9/AI/AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BrainComponent.h"
#include "T9/BlackBoard_Keys.h"


// Sets default values
ACharacterActor::ACharacterActor() :
	WidgetComponent(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitalLocation = GetActorLocation();
	if (WidgetComponent) {
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, HealthBarHeight));
		if (WidgetClass != nullptr) {
			WidgetComponent->SetWidgetClass(WidgetClass);
		}
	}
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	MainHandItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainHandItemMesh"));
	MainHandItem->SetupAttachment(GetMesh());
	MainHandItem->SetSimulatePhysics(false);
	MainHandItem->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	OffHandItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OffHandItemMesh"));
	OffHandItem->SetupAttachment(GetMesh());
	OffHandItem->SetSimulatePhysics(false);
	OffHandItem->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//MainHandItemMesh->SetupAttachment(GetMesh());
	MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	ResetHealth();
}



// Called when the game starts or when spawned
void ACharacterActor::BeginPlay()
{
	Super::BeginPlay();
	if (Levels.Num() == 0) Levels.Add(1, FCharacterLevels{});
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);
	//HealthBar
	if (WidgetComponent) {
		if (WidgetClass != nullptr) {
			WidgetComponent->SetWidgetClass(WidgetClass);
			WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, HealthBarHeight));
		}
		HealthBar = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject());
	}
	//Required for Enemies that arnt spawned during runtime.
	if (Levels.Contains(Level)) {
		MaxHealth = Levels[Level].MaxHealth;
		Damage = Levels[Level].BaseDamage;
	}
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
	//Used to for Spacing between characters and other objects
	if (GetCapsuleComponent()) {
		FVector Scale = GetMesh()->GetRelativeScale3D();
		FVector Bounds = GetMesh()->Bounds.BoxExtent;
		const float NewRadius = FMath::Max(Bounds.X, Bounds.Y) * 0.5f * FMath::Max(Scale.X, Scale.Y) ;
		GetCapsuleComponent()->SetCapsuleRadius(NewRadius * CapsuleRadiusMultiplier);
		CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
		CapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();// *GetActorScale3D().Z;
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -CapsuleHeight));
		GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
	}
	if (GetActorScale3D().Z > 1) SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, CapsuleHeight));
	if (!GetController() && NeedsController) {
		SpawnDefaultController();
	}
	Cont = Cast<AAI_Controller>(GetController());
	SheathMainHand();
}

// Called every frame
void ACharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterActor::SpawnInit(AActor* BuildingSpawn, int SpawnLevel, bool Invuln)
{
	SpawnBuilding = BuildingSpawn;
	Level = SpawnLevel;
	BaseCalculate();
	ResetHealth();
	Invulnerable = Invuln;

}

AActor* ACharacterActor::GetSpawnBuilding() {
	return SpawnBuilding;
}

float ACharacterActor::GetCurrentHealth()
{
	return CurrentHealth;
}

void ACharacterActor::SetLevel(int NewLevel)
{
	Level = NewLevel;
}


void ACharacterActor::SetCurrentHealth(float Number)
{
	CurrentHealth = Number;
	if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}

void ACharacterActor::Heal(float Number)
{
	if (Number < 1 && Number > 0) CurrentHealth += Number * GetMaxHealth();
	else CurrentHealth += Number;
	if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}

float ACharacterActor::GetMaxHealth()
{
	return MaxHealth;
}

void ACharacterActor::SetMaxHealth(float Number)
{
	MaxHealth = Number;
}

void ACharacterActor::ResetHealth()
{
	CurrentHealth = MaxHealth;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}


float ACharacterActor::GetDamage() {
	return Damage;
}

float ACharacterActor::GetArmour()
{
	return Armour;
}

void ACharacterActor::TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage)
{
	int ScaledDamage = UKismetMathLibrary::FCeil(AmountOfDamage * ArmourDamageTakenMultiplier);
	if ((!IsDead && TypeDamage == All) || (!IsDead && TypeDamage != TypeOfDamage)) {
		if (!Target || !Target->IsValidLowLevel()) {
			SetTarget(AttackingActor);
		}
		CurrentHealth -= ScaledDamage;
		if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
		if (CurrentHealth <= 0) {
			DeathInit();
		}
		else if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
	}
}

void ACharacterActor::BaseCalculate()
{
	CalculateDamage();
	CalculateMaxHealth();
	CalculateArmour();
	CalculateAttackRange();
	CalculateAttackSpeed();
}

void ACharacterActor::CalculateDamage(int BaseAdditionalDamage, float AdditionalDamageMultiplier)
{
	Damage = 0;
	if (Levels.Contains(Level)) Damage += Levels[Level].BaseDamage;
	else if (Levels.Contains(Levels.Num())) Damage += Levels[Levels.Num()].BaseDamage;
	Damage += BaseAdditionalDamage;
	Damage *= AdditionalDamageMultiplier;
	Damage += ItemModifiers.OffensiveStats.ItemDamageBase;
	Damage *= ItemModifiers.OffensiveStats.ItemDamageMultiplier;
}

void ACharacterActor::CalculateMaxHealth(int BaseAdditionalHealth, float AdditionalHealthMultiplier)
{
	MaxHealth = 0;
	if (Levels.Contains(Level)) MaxHealth +=  Levels[Level].MaxHealth;
	else if (Levels.Contains(Levels.Num())) MaxHealth += Levels[Levels.Num()].MaxHealth;
	MaxHealth += BaseAdditionalHealth;
	MaxHealth *= AdditionalHealthMultiplier;
	MaxHealth += ItemModifiers.DefensiveStats.ItemHealthBase;
	MaxHealth *= ItemModifiers.DefensiveStats.ItemHealthMultiplier;
	if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, MaxHealth);
}

void ACharacterActor::CalculateArmour(int BaseAdditionalArmour, float AdditionalArmourMultiplier)
{
	Armour = 0;
	if (Levels.Contains(Level)) Armour += Levels[Level].Armour;
	else if (Levels.Contains(Levels.Num())) Armour += Levels[Levels.Num()].Armour;
	Armour += BaseAdditionalArmour;
	Armour *= AdditionalArmourMultiplier;
	Armour += ItemModifiers.DefensiveStats.ItemDefenceBase;
	Armour *= ItemModifiers.DefensiveStats.ItemDefenceMultiplier;
	ArmourDamageTakenMultiplier = UKismetMathLibrary::Exp(-Armour / 1000);
}

void ACharacterActor::CalculateAttackRange(int BaseAdditionalAttackRange, float AdditionalAttackRangeMultiplier)
{
	AttackRange = 0;
	if (Levels.Contains(Level)) AttackRange += Levels[Level].AttackRange;
	else if (Levels.Contains(Levels.Num())) MaxHealth += Levels[Levels.Num()].AttackRange;
	AttackRange += BaseAdditionalAttackRange;
	AttackRange *= AdditionalAttackRangeMultiplier;
	AttackRange += ItemModifiers.OffensiveStats.ItemAttackRangeBase;
	AttackRange *= ItemModifiers.OffensiveStats.ItemAttackRangeMultiplier;
}


void ACharacterActor::CalculateAttackSpeed(int BaseAdditionalAttackSpeed, float AdditionalAttackSpeedMultiplier)
{
	AttackSpeed = 0;
	if (Levels.Contains(Level)) AttackSpeed += Levels[Level].AttackSpeed;
	else if (Levels.Contains(Levels.Num())) AttackSpeed += Levels[Levels.Num()].AttackSpeed;
	AttackSpeed += BaseAdditionalAttackSpeed;
	AttackSpeed *= AdditionalAttackSpeedMultiplier;
	AttackSpeed += ItemModifiers.OffensiveStats.ItemAttackSpeedBase;
	AttackSpeed *= ItemModifiers.OffensiveStats.ItemAttackSpeedMultiplier;
	AttackInterval = 10 * UKismetMathLibrary::Exp(-AttackSpeed / 100);
}

void ACharacterActor::DeathInit() {
	IsDead = true;
	GetCapsuleComponent()->SetCanEverAffectNavigation(true);
	if (Levels.Contains(Level)) {
		PS->AddCurrentXP(Levels[Level].KillXP);
		PS->AddGold(Levels[Level].KillGold);
	}
	else if (Levels.Contains(Levels.Num())) {
		PS->AddCurrentXP(Levels[Levels.Num()].KillXP);
		PS->AddGold(Levels[Levels.Num()].KillGold);
	}
	Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = 0;
	FTimerDelegate Delegate;
	Delegate.BindLambda([this] { Destroy(); });
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, Delegate, DeathTime, false);
	if (SpawnBuilding) {
		UBuildingSpawnComponent* SpawnComponent = Cast<UBuildingSpawnComponent>(SpawnBuilding->GetComponentByClass(UBuildingSpawnComponent::StaticClass()));
		if (SpawnComponent) {
			SpawnComponent->CurrentSpawnCount--;
			SpawnComponent->Respawn();
		}
	}
}

void ACharacterActor::ChangeMovementSpeed(float NewSpeed)
{
	MovementComponent->MaxWalkSpeed = NewSpeed;
}


DamageType ACharacterActor::GetDamageType()
{
	return TypeOfDamage;
}

bool ACharacterActor::IsDamageable()
{
	if (Invulnerable || IsDead) return false;
	else return true;
}

float ACharacterActor::GetAttackRange() {
	return AttackRange;
}

float ACharacterActor::GetAttackSpeed()
{
	return AttackSpeed;
}

float ACharacterActor::GetAttackInterval()
{
	return AttackInterval;
}

void ACharacterActor::Attack()
{
	EquipMainHand();
	if (AttackStreak >= AttackStreakForSpecial) SpecialAttack();
	else {
		CalculateDamage();
		if (Projectile) {
			FActorSpawnParameters SpawnParams;
			AProjectile* SpawnedActorRef = GetWorld()->SpawnActor<AProjectile>(Projectile, GetActorLocation() + RelativeProjectileSpawnLocation, FRotator(0), SpawnParams);
			SpawnedActorRef->ProjectileInnit(Target, Damage, this, ProjectileDelay, TypeOfDamage);
		}
		else if (TargetInterface) {
			TargetInterface->TakeDamage(this, Damage, TypeOfDamage);
		}
		if(AttackMontage) PlayAnimMontage(AttackMontage, 1, AttackMontage->GetSectionName(AttackStreak));
		AttackStreak++;
	}
}

void ACharacterActor::SpecialAttack()
{
	AttackStreak = 0;
	if (TargetInterface) TargetInterface->TakeDamage(this, Damage, TypeOfDamage);
	if(SpecialAttackMontage) PlayAnimMontage(SpecialAttackMontage);
}

void ACharacterActor::ChangePhase(int NewPhase)
{
	//Needs to be overrided in characters which phases
}

void ACharacterActor::SetTarget(AActor* NewTarget)
{
	Target = NewTarget;
	TargetInterface = Cast<IDamageInterface>(Target);
	if (Cont) {
		Cont->GetBlackboard()->SetValueAsObject(bb_keys::combat_target, Target);
		if (Target) Cont->BrainComponent->RestartLogic();
	}
}

bool ACharacterActor::CheckIfDead() {
	return IsDead;
}

void ACharacterActor::SheathMainHand()
{
	if (MainHandItem) {
		MainHandItem->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("spine_03"));
		if (Equipment.MainHand) MainHandItem->SetRelativeTransform(Equipment.MainHand->GetItemSheathedTransform());
		else if (Equipment.DefaultMainHand) MainHandItem->SetRelativeTransform(Equipment.DefaultMainHandTransformSheathed);
	}
}

void ACharacterActor::EquipMainHand()
{
	if (MainHandItem) {
		MainHandItem->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("weaponShield_R"));
		if (Equipment.MainHand) MainHandItem->SetRelativeTransform(Equipment.MainHand->GetItemEquipedTransform());
		else if (Equipment.DefaultMainHand) MainHandItem->SetRelativeTransform(Equipment.DefaultMainHandTransformEquiped);
	}
}

void ACharacterActor::AddMainHand(AItemActor* NewMainHand)
{
	if (NewMainHand) {
		Equipment.MainHand = NewMainHand;
		if (UAnimMontage* NewAttackMontage = NewMainHand->GetItemAnimation(GetMesh()->SkeletalMesh->Skeleton)) AttackMontage = NewAttackMontage;
		MainHandItem->SetStaticMesh(Equipment.MainHand->GetItemMesh());
		ItemModifiers += Equipment.MainHand->GetItemModifiers();
		BaseCalculate();
		SheathMainHand();
	} 
}

void ACharacterActor::ResetEquipment()
{
	ItemModifiers = FItemModifiers{};
	if (Equipment.DefaultMainHand) {
		Equipment.MainHand = nullptr;
		MainHandItem->SetStaticMesh(Equipment.DefaultMainHand);
		MainHandItem->SetRelativeTransform(Equipment.DefaultMainHandTransformSheathed);
		AttackMontage = Equipment.DefaultAttackMontage;
	}
	else {
		MainHandItem->SetStaticMesh(NULL);
	}
	if (Equipment.DefaultOffHand) {
		Equipment.OffHand = nullptr;
		OffHandItem->SetStaticMesh(Equipment.DefaultOffHand);
	}
	else {
		OffHandItem->SetStaticMesh(NULL);
	}
	BaseCalculate();
}


//Character Invulnerability

bool ACharacterActor::CheckInvulnerable()
{
	return Invulnerable;
}

void ACharacterActor::ToggleInvulnerable(bool Input)
{
	Invulnerable = Input;
}

FCharacterLevels ACharacterActor::GetCurrentBaseStats()
{
	if (Levels.Contains(Level)) return Levels[Level];
	return FCharacterLevels();
}

FCharacterLevels ACharacterActor::GetUpgradeBaseStats()
{
	if (Levels.Contains(Level+1)) return Levels[Level+1];
	else if (Levels.Contains(Level)) return Levels[Level];
	return FCharacterLevels();
}

void ACharacterActor::SetSelected()
{
	if (GetMesh()) GetMesh()->SetRenderCustomDepth(true);
}

void ACharacterActor::SetUnSelected()
{
	if (GetMesh()) GetMesh()->SetRenderCustomDepth(false);
}


USkeletalMesh* ACharacterActor::MergeMeshes(const FSkeletalMeshMergeParams& Params)
{
	TArray<USkeletalMesh*> MeshesToMergeCopy = Params.MeshesToMerge;
	MeshesToMergeCopy.RemoveAll([](USkeletalMesh* InMesh)
		{
			return InMesh == nullptr;
		});
	if (MeshesToMergeCopy.Num() <= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Must provide multiple valid Skeletal Meshes in order to perform a merge."));
		return nullptr;
	}
	EMeshBufferAccess BufferAccess = Params.bNeedsCpuAccess ?
		EMeshBufferAccess::ForceCPUAndGPU :
		EMeshBufferAccess::Default;
	TArray<FSkelMeshMergeSectionMapping> SectionMappings;
	//TArray<FSkelMeshMergeUVTransforms> UvTransforms;
	//ToMergeParams(Params.MeshSectionMappings, SectionMappings);
	//ToMergeParams(Params.UVTransformsPerMesh, UvTransforms);
	bool bRunDuplicateCheck = false;
	USkeletalMesh* BaseMesh = NewObject<USkeletalMesh>();
	if (Params.Skeleton && Params.bSkeletonBefore)
	{
		BaseMesh->Skeleton = Params.Skeleton;
		bRunDuplicateCheck = true;
		for (USkeletalMeshSocket* Socket : BaseMesh->GetMeshOnlySocketList())
		{
			if (Socket)
			{
			}
		}
		for (USkeletalMeshSocket* Socket : BaseMesh->Skeleton->Sockets)
		{
			if (Socket)
			{
			}
		}
	}
	FSkeletalMeshMerge Merger(BaseMesh, MeshesToMergeCopy, SectionMappings, Params.StripTopLODS, BufferAccess);
	if (!Merger.DoMerge())
	{
		return nullptr;
	}
	if (Params.Skeleton && !Params.bSkeletonBefore)
	{
		BaseMesh->Skeleton = Params.Skeleton;
	}
	if (bRunDuplicateCheck)
	{
		TArray<FName> SkelMeshSockets;
		TArray<FName> SkelSockets;
		for (USkeletalMeshSocket* Socket : BaseMesh->GetMeshOnlySocketList())
		{
			if (Socket)
			{
				SkelMeshSockets.Add(Socket->GetFName());
			}
		}
		for (USkeletalMeshSocket* Socket : BaseMesh->Skeleton->Sockets)
		{
			if (Socket)
			{
				SkelSockets.Add(Socket->GetFName());
			}
		}
		TSet<FName> UniqueSkelMeshSockets;
		TSet<FName> UniqueSkelSockets;
		UniqueSkelMeshSockets.Append(SkelMeshSockets);
		UniqueSkelSockets.Append(SkelSockets);
		int32 Total = SkelSockets.Num() + SkelMeshSockets.Num();
		int32 UniqueTotal = UniqueSkelMeshSockets.Num() + UniqueSkelSockets.Num();
		UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocketCount: %d | SkelSocketCount: %d | Combined: %d"), SkelMeshSockets.Num(), SkelSockets.Num(), Total);
		UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocketCount: %d | SkelSocketCount: %d | Combined: %d"), UniqueSkelMeshSockets.Num(), UniqueSkelSockets.Num(), UniqueTotal);
		UE_LOG(LogTemp, Warning, TEXT("Found Duplicates: %s"), *((Total != UniqueTotal) ? FString("True") : FString("False")));
	}
	return BaseMesh;
}