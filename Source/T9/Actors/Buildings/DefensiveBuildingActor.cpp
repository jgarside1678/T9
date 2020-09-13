// Fill out your copyright notice in the Description page of Project Settings.
#include "DefensiveBuildingActor.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "T9/Interfaces/DamageInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"


#include "SkeletalMeshMerge.h"
#include "Components/SkeletalMeshComponent.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/Skeleton.h"

ADefensiveBuildingActor::ADefensiveBuildingActor() {
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(StaticMeshComponent);
}

void ADefensiveBuildingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADefensiveBuildingActor::SetTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("Set Target Called"));
	TArray<AActor*> CollidingActors;
	GetOverlappingActors(CollidingActors, AEnemyCharacter::StaticClass());
	if ((Target == nullptr && CollidingActors.Num() > 0 && this->IsDead == false) || (Target->IsValidLowLevel() && Target->IsPendingKill() && CollidingActors.Num() > 0) && this->IsDead == false) {
		switch (AttackPiority) {
		case Closest:
			float ClosestDistance;
			for (int x = 0; x < CollidingActors.Num(); x++) {
				float Distance = (GetActorLocation() - CollidingActors[x]->GetActorLocation()).Size();
				if (Target == nullptr || Distance < ClosestDistance || Target->IsPendingKill()) {
					ClosestDistance = Distance;
					Target = CollidingActors[x];
				}
			}
			break;
		case HighestHP:
			UE_LOG(LogTemp, Warning, TEXT("Target Method Not Implemented Yet"));
			break;
		case LowestHP:
			UE_LOG(LogTemp, Warning, TEXT("Target Method Not Implemented Yet"));
			break;
		case Random:
			UE_LOG(LogTemp, Warning, TEXT("Target Method Not Implemented Yet"));
			break;
		default:
			break;
		}
		UE_LOG(LogTemp, Warning, TEXT("New Target"));
		TargetInterface = Cast<IDamageInterface>(Target);
		AttackTarget();
	}
}

void ADefensiveBuildingActor::AttackTarget()
{
	if (!Disabled) {
		if (Target != nullptr && !Target->IsPendingKill()) {
			if (TargetInterface->IsDamageable()) {
				FActorSpawnParameters SpawnParams;
				if (BuildingDefender) {
					UE_LOG(LogTemp, Warning, TEXT("Attack2"));
					ProjectileSpawn->SetWorldLocation(BuildingDefender->GetSocketLocation("hand_r"));
					if (DefenderAttackAnimation)	BuildingDefender->PlayAnimation(DefenderAttackAnimation, false);
				}
				FVector Location = ProjectileSpawn->GetComponentLocation();
				FRotator Rotation = ProjectileSpawn->GetRelativeRotation();
				if (Projectile && RecentlyRendered) {
					AProjectile* SpawnedActorRef = GetWorld()->SpawnActor<AProjectile>(Projectile, Location, Rotation, SpawnParams);
					SpawnedActorRef->ProjectileInnit(Target, GetDamage(), this, ProjectileDelay, Enemy);
				}
				else TargetInterface->TakeDamage(this, GetDamage(), Enemy);
			}
			GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ADefensiveBuildingActor::AttackTarget, AttackSpeedMultiplier, false, AttackSpeedMultiplier);
		}
		else SetTarget();
	}
}

void ADefensiveBuildingActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	RecentlyRendered = WasRecentlyRendered(0.2);
	if (RecentlyRendered) {
		if (Target && TurretStaticMeshComponent) {
			FVector AimLocation = Target->GetActorLocation() + FVector(0, 0, 150);
			FRotator Rot = UKismetMathLibrary::FindLookAtRotation(TurretStaticMeshComponent->GetComponentLocation(), AimLocation);
			TurretRotation = UKismetMathLibrary::RInterpTo(TurretStaticMeshComponent->GetRelativeRotation(), Rot - GetActorRotation(), DeltaTime, 3);
			TurretStaticMeshComponent->SetRelativeRotation(FRotator(0, TurretRotation.Yaw, 0));
			ProjectileSpawn->SetRelativeRotation(TurretRotation);
		}
		else if (Target && BuildingDefender) {
			FVector AimLocation = Target->GetActorLocation() + FVector(0, 0, 150);
			FRotator Rot = UKismetMathLibrary::FindLookAtRotation(BuildingDefender->GetComponentLocation(), AimLocation);
			TurretRotation = UKismetMathLibrary::RInterpTo(BuildingDefender->GetRelativeRotation(), Rot - GetActorRotation(), DeltaTime, 3);
			BuildingDefender->SetRelativeRotation(FRotator(0, TurretRotation.Yaw, 0));
			ProjectileSpawn->SetRelativeRotation(TurretRotation);
		}
	}
}


void ADefensiveBuildingActor::MeshInit() {
	if (MeshPeices.Num() > 0) {
		TArray<USkeletalMesh*> mergeMeshes;
		mergeMeshes.Empty(MeshPeices.Num());

		for (int32 i = 0; i < MeshPeices.Num(); i++)
		{
			if (MeshPeices[i] == nullptr)
				continue;

			mergeMeshes.Add(MeshPeices[i]);
		}

		if (mergeMeshes.Num() > 0)
		{
			USkeletalMesh* targetMesh = NewObject<USkeletalMesh>(USkeletalMesh::StaticClass(), USkeletalMesh::StaticClass(), FName("MergedMesh"), RF_Transient);
			targetMesh->Skeleton = MeshPeices[0]->Skeleton;
			//targetMesh->SetLODSettings(GetMesh()->SkeletalMesh->LODSettings);
			TArray<FSkelMeshMergeSectionMapping> sectionMappings;
			FSkeletalMeshMerge merger(targetMesh, mergeMeshes, sectionMappings, 0);
			const bool mergeStatus = merger.DoMerge();
			check(mergeStatus == true);

			BuildingDefender->SetSkeletalMesh(targetMesh);
		}
	}
}


USkeletalMesh* ADefensiveBuildingActor::MergeMeshes(const FSkeletalMeshMergeParams& Params)
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
                UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocket: %s"), *(Socket->SocketName.ToString()));
            }
        }
        for (USkeletalMeshSocket* Socket : BaseMesh->Skeleton->Sockets)
        {
            if (Socket)
            {
                UE_LOG(LogTemp, Warning, TEXT("SkelSocket: %s"), *(Socket->SocketName.ToString()));
            }
        }
    }
    FSkeletalMeshMerge Merger(BaseMesh, MeshesToMergeCopy, SectionMappings, Params.StripTopLODS, BufferAccess);
    if (!Merger.DoMerge())
    {
        UE_LOG(LogTemp, Warning, TEXT("Merge failed!"));
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
                UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocket: %s"), *(Socket->SocketName.ToString()));
            }
        }
        for (USkeletalMeshSocket* Socket : BaseMesh->Skeleton->Sockets)
        {
            if (Socket)
            {
                SkelSockets.Add(Socket->GetFName());
                UE_LOG(LogTemp, Warning, TEXT("SkelSocket: %s"), *(Socket->SocketName.ToString()));
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




