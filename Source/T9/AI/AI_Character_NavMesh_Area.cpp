// Copyright T9 2020


#include "AI_Character_NavMesh_Area.h"


UAI_Character_NavMesh_Area::UAI_Character_NavMesh_Area(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DrawColor = FColor(153, 50, 204);	// Purple
	DefaultCost = 10.f;
	FixedAreaEnteringCost = 1000.0f;
}