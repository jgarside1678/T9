#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace bb_keys
{
	//Global
	TCHAR const* const move_location = TEXT("MoveToLocation");
	TCHAR const* const target_actor = TEXT("Target");
	//Enemy Specific
	TCHAR const* const target_is_in_range = TEXT("TargetIsInRange");
	//Alliance Specific
	TCHAR const* const inventory_is_full = TEXT("FullInventory");
}