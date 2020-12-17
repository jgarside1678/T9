#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace bb_keys
{
	//Global
	TCHAR const* const move_location = TEXT("MoveToLocation");
	TCHAR const* const combat_target = TEXT("CombatTarget");
	TCHAR const* const utility_target = TEXT("UtilityTarget");
	TCHAR const* const hunt = TEXT("Hunt");
	TCHAR const* const resource = TEXT("Resource");
	TCHAR const* const attacker = TEXT("Attacker");
	TCHAR const* const attack_interval = TEXT("AttackInterval");
	//Enemy Specific
	TCHAR const* const target_is_in_range = TEXT("TargetIsInRange");
	TCHAR const* const target_is_dead = TEXT("TargetIsDead");
	//Alliance Specific
	TCHAR const* const inventory_is_full = TEXT("FullInventory");
	TCHAR const* const command_location = TEXT("CommandLocation");
}