// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

void UHealthBarWidget::SetHealthPercent(float CurrentHealth, float MaxHealth)
{
	float Percent = CurrentHealth / MaxHealth;
	Health_Bar->SetPercent(Percent);
}

void UHealthBarWidget::NativeConstruct() {

}