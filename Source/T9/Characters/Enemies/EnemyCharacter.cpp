// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "T9/MainPlayerState.h"
#include "Components/CapsuleComponent.h"
#include "T9/Actors/Items/ItemActor.h"
#include "T9/Widgets/HealthBarWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "T9/AI/AI_Controller.h"
#include "Navigation/CrowdFollowingComponent.h"

AEnemyCharacter::AEnemyCharacter() {
	TargetBuildings = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("WidgetBlueprint'/Game/UI/EnemyHealthBar.EnemyHealthBar_C'"));
	if (widget.Succeeded()) {
		WidgetClass = widget.Class;
	}
	TypeOfDamage = Enemy;
	GetMesh()->SetCustomDepthStencilValue(1);
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();
	if (PS) PS->SpawnedEnemyCharacters.Add(this);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	if (Cont) {
		Cont->GetCrowdManager()->SetAvoidanceGroup(2);
		Cont->GetCrowdManager()->SetGroupsToAvoid(6);
		Cont->GetCrowdManager()->SetCrowdCollisionQueryRange(GetCapsuleComponent()->GetScaledCapsuleRadius() + 2000);
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::GenerateLoot() {
	int Total = 0, CurrentMin = 1, CurrentMax = 0;
	for (int x = 0; x < DropTable.Num(); x++) {
		Total += DropTable[x].LootChance;
	}
	int Random = FMath::RandRange(1, Total);
	for (int x = 0; x < DropTable.Num(); x++) {
		CurrentMax += DropTable[x].LootChance;
		if (Random >= CurrentMin && Random <= CurrentMax && DropTable[x].ItemClass) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(DropTable[x].ItemClass, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		}
		else CurrentMin += CurrentMax;
	}
}

void AEnemyCharacter::DeathInit() {
	Super::DeathInit();
	GenerateLoot();
}