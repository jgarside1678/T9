// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCharacter.h"
#include "ResourceActor.h"

// Sets default values
AResourceCharacter::AResourceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called to bind functionality to input
void AResourceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AResourceCharacter::Init(AResourceActor* OwningResource, FVector SpawnLocation)
{
	ParentResource = OwningResource;
	InitialLocation = SpawnLocation;
	if (!GetController()) {
		FTimerHandle ControllerTimerHandle;
		GetWorldTimerManager().SetTimer(ControllerTimerHandle, this, &AResourceCharacter::SpawnDefaultController, 2, false, 2);
	}
}

bool AResourceCharacter::CheckIfDead() {
	return Dead;
}


AResourceActor* AResourceCharacter::GetParentResource()
{
	return ParentResource;
}

void AResourceCharacter::SetSelected()
{
	ParentResource->SetSelected();
}

void AResourceCharacter::SetUnSelected()
{
	ParentResource->SetUnSelected();
}

void AResourceCharacter::TakeDamage(AActor* AttackingActor, float AmountOfDamage, DamageType TypeDamage)
{
	if (!Dead) {
		Health -= AmountOfDamage;
		if (Health <= 0) {
			Dead = true;
			Controller->UnPossess();
			GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AResourceCharacter::DeathInit, DecayDuration, false, DecayDuration);
		}
		else if(!Target) {
			Target = AttackingActor;
			TargetInterface = Cast<IDamageInterface>(Target);
		}
	}
}

void AResourceCharacter::DeathInit() {
	Destroy();
	ParentResource->ReduceCurrentSpawnCount(1);
}

void AResourceCharacter::Attack() {
	if (TargetInterface) TargetInterface->TakeDamage(this, Damage, DamageType::All);
	if(AttackMontage) PlayAnimMontage(AttackMontage, 1);
}