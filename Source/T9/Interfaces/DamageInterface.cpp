// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageInterface.h"

// Add default functionality here for any ITakeDamageInterface functions that are not pure virtual.

void IDamageInterface::DamageEnemy(AActor* Actor, float AmountOfDamage)
{
}

void IDamageInterface::TakeDamage(AActor* Actor, float AmountOfDamage)
{
}

bool IDamageInterface::CheckIfDead() {
	return false;
}