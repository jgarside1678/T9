// Copyright T9 2020

#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"
#include "UObject/ObjectMacros.h"
#include "AI_Character_NavMesh_Area.generated.h"

/**
 * 
 */
UCLASS()
class T9_API UAI_Character_NavMesh_Area : public UNavArea
{
	GENERATED_BODY()

public:

	UAI_Character_NavMesh_Area(const FObjectInitializer& ObjectInitializer);
};
