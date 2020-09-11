// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceQuickSelect.h"

UResourceQuickSelect::UResourceQuickSelect(const FObjectInitializer& ObjectInit) : Super(ObjectInit) {

}

void UResourceQuickSelect::Init(AResourceActor* MenuResource)
{
	if(MenuResource) Resource = MenuResource;
}
