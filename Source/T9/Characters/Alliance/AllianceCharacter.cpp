// Fill out your copyright notice in the Description page of Project Settings.


#include "AllianceCharacter.h"
#include "T9/MainPlayerState.h"
#include "T9/Widgets/HealthBarWidget.h"
#include "SkeletalMeshMerge.h"
#include "Components/SkeletalMeshComponent.h"
#include "T9/AI/AI_Controller.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/Skeleton.h"
#include "DrawDebugHelpers.h"
#include "T9/Characters/Enemies/EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "T9/BlackBoard_Keys.h"

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
}

void AAllianceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAllianceCharacter::MeshInit() {
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

			GetMesh()->SetSkeletalMesh(targetMesh);
		}
	}
}



//static void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMapping>& OutSectionMappings)
//{
//    if (InSectionMappings.Num() > 0)
//    {
//        OutSectionMappings.AddUninitialized(InSectionMappings.Num());
//        for (int32 i = 0; i < InSectionMappings.Num(); ++i)
//        {
//            OutSectionMappings[i].SectionIDs = InSectionMappings[i].SectionIDs;
//        }
//    }
//};
//static void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMapping>& InUVTransformsPerMesh, TArray<FSkelMeshMergeUVTransforms>& OutUVTransformsPerMesh)
//{
//    if (InUVTransformsPerMesh.Num() > 0)
//    {
//        OutUVTransformsPerMesh.Empty();
//        OutUVTransformsPerMesh.AddUninitialized(InUVTransformsPerMesh.Num());
//        for (int32 i = 0; i < InUVTransformsPerMesh.Num(); ++i)
//        {
//            TArray<TArray<FTransform>>& OutUVTransforms = OutUVTransformsPerMesh[i].UVTransformsPerMesh;
//            const TArray<FSkelMeshMergeUVTransform>& InUVTransforms = InUVTransformsPerMesh[i].UVTransformsPerMesh;
//            if (InUVTransforms.Num() > 0)
//            {
//                OutUVTransforms.Empty();
//                OutUVTransforms.AddUninitialized(InUVTransforms.Num());
//                for (int32 j = 0; j < InUVTransforms.Num(); j++)
//                {
//                    OutUVTransforms[i] = InUVTransforms[i].UVTransforms;
//                }
//            }
//        }
//    }
//};


USkeletalMesh* AAllianceCharacter::MergeMeshes(const FSkeletalMeshMergeParams& Params)
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

void AAllianceCharacter::Command(FHitResult Hit)
{
    CommandEnemyTarget = Cast<AEnemyCharacter>(Hit.Actor);
    CommandAllianceTarget = Cast<AAllianceCharacter>(Hit.Actor);
    CommandBuildingTarget = Cast<ABuildingActor>(Hit.Actor);
    if (!CommandEnemyTarget && !CommandAllianceTarget && !CommandBuildingTarget) CommandLocation = FVector(Hit.Location.X, Hit.Location.Y, 10);
    DrawDebugLine(GetWorld(), CommandLocation, FVector(CommandLocation.X, CommandLocation.Y, 3000), FColor::Blue, false, 20, 0, 10);
    if (Cont) {
        Cont->GetBlackboard()->SetValueAsVector(bb_keys::command_location, CommandLocation);
        Cont->Reset();
    }

}

FVector AAllianceCharacter::GetCommandLocation() {
    return CommandLocation;
}

void AAllianceCharacter::SpawnInit(AActor* BuildingSpawn, int SpawnLevel, bool Invuln, bool SpawnController)
{
    Super::SpawnInit(BuildingSpawn, SpawnLevel, Invuln, SpawnController);
    Cont = Cast<AAI_Controller>(GetController());
}