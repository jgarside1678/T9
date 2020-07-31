// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain_Grass.h"

ATerrain_Grass::ATerrain_Grass() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/AdvancedVillagePack/Meshes/SM_GrassPatch_Var01.SM_GrassPatch_Var01'"));
	if(Mesh.Succeeded()) StaticMeshComponent->SetStaticMesh(Mesh.Object);
}