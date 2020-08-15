// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectMenuWidget.h"

USelectMenuWidget::USelectMenuWidget(const FObjectInitializer& ObjectInit) : Super(ObjectInit)
{

}

void USelectMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USelectMenuWidget::UpdateMenu(AActor* Object)
{
}

void USelectMenuWidget::TabLeft()
{
	--CurrentTab;
}

void USelectMenuWidget::TabRight()
{
	++CurrentTab;
}

void USelectMenuWidget::SetTab(ESelectTab Tab)
{
}
