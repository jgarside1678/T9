// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile_Ballista_Arrow.h"
#include "Components/BoxComponent.h"

AProjectile_Ballista_Arrow::AProjectile_Ballista_Arrow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	ProjectileSpeed = 1.9;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/bow_arrow.bow_arrow'"));
	if (Mesh.Succeeded()) {
		StaticMeshComp->SetStaticMesh(Mesh.Object);
		FVector BoxExtent = StaticMeshComp->GetStaticMesh()->GetBoundingBox().GetExtent();
		BoxCollider->SetBoxExtent(BoxExtent);
		StaticMeshComp->SetRelativeLocation(FVector(-BoxExtent.X, 0, 0));
		StaticMeshComp->SetRelativeScale3D(FVector(1.7));
	}
}