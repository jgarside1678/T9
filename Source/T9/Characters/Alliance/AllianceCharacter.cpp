// Fill out your copyright notice in the Description page of Project Settings.


#include "AllianceCharacter.h"
#include "T9/MainPlayerState.h"
#include "T9/Widgets/HealthBarWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/Skeleton.h"
#include "DrawDebugHelpers.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "T9/AI/AI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/BlackBoard_Keys.h"
#include "BrainComponent.h"
#include "T9/Actors/Resources/ResourceCharacter.h"
#include "T9/Actors/Resources/ResourceActor.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Navigation/CrowdFollowingComponent.h"

AAllianceCharacter::AAllianceCharacter() {
	static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("WidgetBlueprint'/Game/UI/AllianceHealthBar.AllianceHealthBar_C'"));
	if (widget.Succeeded()) {
		WidgetClass = widget.Class;
	}
    TypeOfDamage = Alliance;
    GetMesh()->SetCustomDepthStencilValue(2);

}

void AAllianceCharacter::BeginPlay() {
	Super::BeginPlay();
	if (PS) PS->SpawnedAllianceCharacters.Add(this);
    GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel4);
    if (Cont) {
        Cont->GetCrowdManager()->SetAvoidanceGroup(1);
        Cont->GetCrowdManager()->SetGroupsToAvoid(1);
        Cont->GetCrowdManager()->SetGroupsToIgnore(4);
        //Cont->GetCrowdManager()->SetCrowdOptimizeTopology(true);
        //Cont->GetCrowdManager()->SetCrowdOptimizeVisibility(true);
        //Cont->GetCrowdManager()->SetCrowdPathOffset(true);
        //Cont->GetCrowdManager()->SetCrowdSlowdownAtGoal(false);
        //Cont->GetCrowdManager()->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
        //Cont->GetCrowdManager()->SetCrowdPathOptimizationRange(1000);
        Cont->GetCrowdManager()->SetCrowdCollisionQueryRange(GetCapsuleComponent()->GetScaledCapsuleRadius()+2000);
    }
}

void AAllianceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAllianceCharacter::Command(FHitResult Hit)
{
    CommandEnemyTarget = Cast<AEnemyCharacter>(Hit.Actor);
    CommandAllianceTarget = Cast<AAllianceCharacter>(Hit.Actor);
    CommandBuildingTarget = Cast<ABuildingActor>(Hit.Actor);
    CommandedResourceActor = Cast<AResourceActor>(Hit.Actor);
    CommandedResourceCharacter = Cast<AResourceCharacter>(Hit.Actor);
    if (Cont) {
        if (!CommandEnemyTarget && !CommandAllianceTarget && !CommandBuildingTarget && !CommandedResourceActor && !CommandedResourceCharacter) {
            CommandLocation = FVector(Hit.Location.X, Hit.Location.Y, 10);
            Cont->GetBlackboard()->SetValueAsVector(bb_keys::command_location, CommandLocation);
            DrawDebugLine(GetWorld(), CommandLocation, FVector(CommandLocation.X, CommandLocation.Y, 3000), FColor::Blue, false, 20, 0, 10);
        }
        else {
            Cont->GetBlackboard()->ClearValue(bb_keys::command_location);
            Cont->GetBlackboard()->ClearValue(bb_keys::utility_target);
        }
        Cont->BrainComponent->RestartLogic();
        
    }
}

FVector AAllianceCharacter::GetCommandLocation() {
    return CommandLocation;
}

void AAllianceCharacter::SpawnInit(AActor* BuildingSpawn, int SpawnLevel, bool Invuln)
{
    Super::SpawnInit(BuildingSpawn, SpawnLevel, Invuln);
}