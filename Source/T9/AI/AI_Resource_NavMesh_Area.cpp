// Copyright T9 2020


#include "AI_Resource_NavMesh_Area.h"

UAI_Resource_NavMesh_Area::UAI_Resource_NavMesh_Area(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DrawColor = FColor(127, 221, 240);	// Blue
	DefaultCost = 1.f;
	FixedAreaEnteringCost = 1000.0f;
}