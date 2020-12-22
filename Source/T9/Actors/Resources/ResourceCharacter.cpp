// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCharacter.h"
#include "ResourceActor.h"
#include "T9/AI/AI_Controller.h"

// Sets default values
AResourceCharacter::AResourceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TypeOfDamage = DamageType::All;
}

// Called when the game starts or when spawned
void AResourceCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AResourceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AResourceCharacter::Init(AResourceActor* OwningResource, FVector SpawnLocation)
{
	ParentResource = OwningResource;
	InitialLocation = SpawnLocation;
	Level = 1;
	BaseCalculate();
	ResetHealth();
	if (!GetController()) SpawnDefaultController();
	Invulnerable = false;

	Cont = Cast<AAI_Controller>(GetController());
}




AResourceActor* AResourceCharacter::GetParentResource()
{
	return ParentResource;
}

void AResourceCharacter::SetSelected()
{
	if (ParentResource)ParentResource->SetSelected();
}

void AResourceCharacter::SetUnSelected()
{
	if (ParentResource) ParentResource->SetUnSelected();
}

void AResourceCharacter::TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage)
{
	UE_LOG(LogTemp, Warning, TEXT("Take Damage"));
	if (!IsDead) {
		CurrentHealth -= AmountOfDamage;
		if (CurrentHealth <= 0) {
			IsDead = true;
			Controller->UnPossess();
			GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AResourceCharacter::DeathInit, DecayDuration, false, DecayDuration);
		}
		else if(!Target) {
			SetTarget(AttackingActor);
		}
	}
}

void AResourceCharacter::DeathInit() {
	Destroy();
	if(ParentResource) ParentResource->ReduceCurrentSpawnCount(1);
}

void AResourceCharacter::Attack() {
	if (TargetInterface) TargetInterface->TakeDamage(this, Damage, DamageType::All);
	if(AttackMontage) PlayAnimMontage(AttackMontage, 1);
}