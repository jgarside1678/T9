// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "T9/Widgets/HealthBarWidget.h"
#include "T9/Actors/Projectiles/Projectile.h"
#include "T9/MainPlayerState.h"
#include "T9/Actors/Components/BuildingSpawnComponent.h"
#include "T9/MainPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	MainHandItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainHandItemMesh"));
	MainHandItemMesh->SetupAttachment(GetMesh());
	MainHandItemMesh->SetSimulatePhysics(false);
	MainHandItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//MainHandItemMesh->SetupAttachment(GetMesh());
	MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
}



// Called when the game starts or when spawned
void ACharacterActor::BeginPlay()
{
	Super::BeginPlay();
	if (Levels.Num() == 0) Levels.Add(1, FCharacterLevels{});
	PC = (AMainPlayerController*)GetWorld()->GetFirstPlayerController();
	PS = (AMainPlayerState*)PC->PlayerState;

	//HealthBar
	if (WidgetComponent) {
		if (WidgetClass != nullptr) {
			WidgetComponent->SetWidgetClass(WidgetClass);
		}
		HealthBar = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject());
	}
	if (Levels.Contains(Level)) {
		Damage = Levels[Level].BaseDamage;
		if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, Levels[Level].MaxHealth);
	}
	//Used to for Spacing between characters and other objects
	if (GetCapsuleComponent()) {
		CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
		CapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();// *GetActorScale3D().Z;
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -CapsuleHeight));
		GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
	}
	if (GetActorScale3D().Z > 1) SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, CapsuleHeight));

	if (MovementComponent) {
		MovementComponent->SetAvoidanceEnabled(true);
		MovementComponent->AvoidanceConsiderationRadius = CapsuleRadius * 2.3;
	}

	SheathMainHand();
}

// Called every frame
void ACharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z < -100) this->Destroy();
}

// Called to bind functionality to input
void ACharacterActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterActor::SpawnInit(AActor* BuildingSpawn, int SpawnLevel, bool Invuln, bool SpawnController)
{
	SpawnBuilding = BuildingSpawn;
	Level = SpawnLevel;
	ResetHealth();
	NeedsController = SpawnController;
	if (!GetController() && NeedsController) {
		FTimerHandle ControllerTimerHandle;
		GetWorldTimerManager().SetTimer(ControllerTimerHandle, this, &ACharacterActor::SpawnDefaultController, 2, false, 2);
	}
	else {
		WidgetComponent->SetVisibility(false);
	}
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
	if (Levels.Contains(Level)) {
		if (CurrentHealth > Levels[Level].MaxHealth) CurrentHealth = Levels[Level].MaxHealth;
		if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, Levels[Level].MaxHealth);
	}
	else if (Levels.Contains(Levels.Num())) {
		if (CurrentHealth > Levels[Levels.Num()].MaxHealth) CurrentHealth = Levels[Levels.Num()].MaxHealth;
		if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, Levels[Levels.Num()].MaxHealth);
	}
}

float ACharacterActor::GetMaxHealth()
{
	if (Levels.Contains(Level)) return  Levels[Level].MaxHealth;
	else if (Levels.Contains(Levels.Num())) return Levels[Levels.Num()].MaxHealth;
	return 0;
}

void ACharacterActor::SetMaxHealth(float Number)
{
	if (Levels.Contains(Level)) {
		Levels[Level].MaxHealth = Number;
		if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, Levels[Level].MaxHealth);
	}
	else if (Levels.Contains(Levels.Num())) {
		Levels[Levels.Num()].MaxHealth = Number;
		if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, Levels[Levels.Num()].MaxHealth);
	}
}

void ACharacterActor::ResetHealth()
{
	if (Levels.Contains(Level)) {
		CurrentHealth = Levels[Level].MaxHealth;
		HealthBar->SetHealthPercent(CurrentHealth, Levels[Level].MaxHealth);
	}
	else if (Levels.Contains(Levels.Num())) {
		CurrentHealth = Levels[Levels.Num()].MaxHealth;
		HealthBar->SetHealthPercent(CurrentHealth, Levels[Levels.Num()].MaxHealth);
	}
}


float ACharacterActor::GetDamage() {
	return Damage;
}

void ACharacterActor::TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage)
{
	if ((!IsDead && TypeDamage == All) || (!IsDead && TypeDamage == TypeOfDamage)) {
		CurrentHealth -= AmountOfDamage;
		if (Levels.Contains(Level)) {
			if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, Levels[Level].MaxHealth);
		}
		else if (Levels.Contains(Levels.Num())) {
			if (HealthBar != nullptr) HealthBar->SetHealthPercent(CurrentHealth, Levels[Levels.Num()].MaxHealth);
		}
		if (CurrentHealth <= 0) {
			DeathInit();
		}
	}
}

void ACharacterActor::CalculateDamage(int BaseAdditionalDamage)
{
	if (Levels.Contains(Level)) {
		Damage = Levels[Level].BaseDamage;
	}
	else if (Levels.Contains(Levels.Num())) Damage = Levels[Levels.Num()].BaseDamage;
	Damage += BaseAdditionalDamage;
}

void ACharacterActor::DeathInit() {
	IsDead = true;
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

void ACharacterActor::DamageEnemy(AActor* Actor, float AmountOfDamage)
{
	IDamageInterface* Enemy = Cast<IDamageInterface>(Actor);
	if (Enemy != nullptr) Enemy->TakeDamage(this, AmountOfDamage);
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
	if (Levels.Contains(Level)) return Levels[Level].AttackRange;
	else if (Levels.Contains(Levels.Num())) return Levels[Levels.Num()].AttackRange;
	return 0;
}

void ACharacterActor::Attack(AActor* Target)
{
	if (AttackStreak >= AttackStreakForSpecial) SpecialAttack(Target);
	else {
		if (Target != CurrentTarget) AttackStreak = 0;
		CurrentTarget = Target;
		CalculateDamage(0);
		if (Projectile) {
			FActorSpawnParameters SpawnParams;
			AProjectile* SpawnedActorRef = GetWorld()->SpawnActor<AProjectile>(Projectile, GetActorLocation(), FRotator(0), SpawnParams);
			DamageType ProjectileDamage = All;
			if (TypeOfDamage == Alliance) ProjectileDamage = Enemy;
			else if (TypeOfDamage == Enemy) ProjectileDamage = Alliance;
			SpawnedActorRef->ProjectileInnit(Target, GetDamage(), this, 0, ProjectileDamage);
		}
		else DamageEnemy(Target, Damage);
		if(AttackMontage) PlayAnimMontage(AttackMontage);
		AttackStreak++;
	}
}

void ACharacterActor::SpecialAttack(AActor* Target)
{
	CurrentTarget = Target;
	DamageEnemy(Target, Damage);
	if(SpecialAttackMontage) PlayAnimMontage(SpecialAttackMontage);
	AttackStreak = 0;
}

void ACharacterActor::ChangePhase(int NewPhase)
{
	//Needs to be overrided in characters which phases
}

bool ACharacterActor::CheckIfDead() {
	return IsDead;
}

void ACharacterActor::SheathMainHand()
{
	if (MainHandItemMesh) {
		MainHandItemMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("spine_03"));
	}
}

void ACharacterActor::EquipMainHand()
{
	if (MainHandItemMesh) {
		MainHandItemMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("weaponShield_R"));
	}
}

bool ACharacterActor::CheckInvulnerable()
{
	return Invulnerable;
}

void ACharacterActor::ToggleInvulnerable(bool Input)
{
	Invulnerable = Input;
}
