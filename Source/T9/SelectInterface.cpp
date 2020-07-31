// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectInterface.h"

// Add default functionality here for any ISelectInterface functions that are not pure virtual.

void ISelectInterface::SetSelected() {

}


void ISelectInterface::SetUnSelected() {

}

float ISelectInterface::GetDamage()
{
	return 0.0f;
}

float ISelectInterface::GetCurrentHealth()
{
	return 1;
}

float ISelectInterface::GetMaxHealth()
{
	return 1;
}

FString ISelectInterface::GetName()
{
	return FString("Name");
}

int ISelectInterface::GetLevel()
{
	return 1;
}
