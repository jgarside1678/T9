// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile_Arrow.h"
#include "Components/BoxComponent.h"

AProjectile_Arrow::AProjectile_Arrow(const FObjectInitializer& ObjectInitializer) : Super() {

	ProjectileSpeed = 1.5;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/bow_arrow.bow_arrow'"));
	if (Mesh.Succeeded()) {
		StaticMeshComp->SetStaticMesh(Mesh.Object);
		FVector BoxExtent = StaticMeshComp->GetStaticMesh()->GetBoundingBox().GetExtent();
		BoxCollider->SetBoxExtent(BoxExtent);
		StaticMeshComp->SetRelativeLocation(FVector(-BoxExtent.X, 0, 0));
	}
}