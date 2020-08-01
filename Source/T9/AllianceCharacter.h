// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterActor.h"
#include "UObject/NoExportTypes.h"
#include "AllianceCharacter.generated.h"



USTRUCT(BlueprintType)
struct T9_API FSkeletalMeshMergeParams
{
    GENERATED_BODY()
    
    FSkeletalMeshMergeParams()
    {
        StripTopLODS = 0;
        bNeedsCpuAccess = false;
        bSkeletonBefore = false;
        Skeleton = nullptr;
    }

    FSkeletalMeshMergeParams(TArray<class USkeletalMesh*> Meshes, class USkeleton* Skele)
    {
        MeshesToMerge = Meshes;
        StripTopLODS = 0;
        bNeedsCpuAccess = false;
        bSkeletonBefore = false;
        Skeleton = Skele;
    }
    // An optional array to map sections from the source meshes to merged section entries
    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //    TArray<FSkelMeshMergeSectionMapping_BP> MeshSectionMappings;
    //// An optional array to transform the UVs in each mesh
    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //    TArray<FSkelMeshMergeUVTransformMapping> UVTransformsPerMesh;
    // The list of skeletal meshes to merge.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<class USkeletalMesh*> MeshesToMerge;
    // The number of high LODs to remove from input meshes
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 StripTopLODS;
    // Whether or not the resulting mesh needs to be accessed by the CPU for any reason (e.g. for spawning particle effects).
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        uint32 bNeedsCpuAccess : 1;
    // Update skeleton before merge. Otherwise, update after.
    // Skeleton must also be provided.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        uint32 bSkeletonBefore : 1;
    // Skeleton that will be used for the merged mesh.
    // Leave empty if the generated skeleton is OK.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        class USkeleton* Skeleton;
};



UCLASS()
class T9_API AAllianceCharacter : public ACharacterActor
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAllianceCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TArray<USkeletalMesh*> MeshPeices;

	UFUNCTION()
		void MeshInit();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Mesh Merge", meta = (UnsafeDuringActorConstruction = "true"))
        static class USkeletalMesh* MergeMeshes(const FSkeletalMeshMergeParams& Params);
};

