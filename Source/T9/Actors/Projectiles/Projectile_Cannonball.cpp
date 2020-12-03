// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Cannonball.h"
#include "Components/BoxComponent.h"

AProjectile_Cannonball::AProjectile_Cannonball(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	ProjectileSpeed = 2.5;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Assets/SiegeWeaponsPackFullPack/Resources/Projectiles/projectile01.projectile01'"));
	if (Mesh.Succeeded()) {
		StaticMeshComp->SetStaticMesh(Mesh.Object);
		FVector BoxExtent = StaticMeshComp->GetStaticMesh()->GetBoundingBox().GetExtent();
		BoxCollider->SetBoxExtent(BoxExtent);
		StaticMeshComp->SetRelativeLocation(FVector(-BoxExtent.X, 0, 0));
		StaticMeshComp->SetRelativeScale3D(FVector(2));
	}
}
