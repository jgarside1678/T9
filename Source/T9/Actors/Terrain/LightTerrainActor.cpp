// Fill out your copyright notice in the Description page of Project Settings.


#include "LightTerrainActor.h"
#include "Components/PointLightComponent.h"

ALightTerrainActor::ALightTerrainActor() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/World/Tower_Defence/Models/Props/Lantern1.Lantern1'"));
	if (Mesh.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(Mesh.Object);
		//StaticMeshComponent->SetWorldScale3D(FVector(6,6,4));
	}
	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightComponent"));
	LightComponent->SetupAttachment(RootComponent);
	LightComponent->SetIntensityUnits(ELightUnits::Lumens);
	LightComponent->SetRelativeLocation(FVector(0,110,220));
	LightComponent->SetLightFalloffExponent(1000);
	LightComponent->SetAttenuationRadius(3000);
	LightComponent->SetSourceRadius(500);
	LightComponent->SetCastShadows(false);
	FLinearColor LightColour = FLinearColor(FMath::RandRange(0, 1), FMath::RandRange(0, 1), FMath::RandRange(0, 1), FMath::RandRange(0, 1));
	LightComponent->SetLightColor(LightColour, true);
}