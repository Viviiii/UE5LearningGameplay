// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/WidgetHealthBar.h"
#include "HUD/HealthBar.h"

void UHealthBar::setPercentHealth(float HP)
{
	if (healthBarW == nullptr) {
		healthBarW = Cast<UWidgetHealthBar>(GetUserWidgetObject());
	}
	
	if (healthBarW && healthBarW->healthBar) {
		healthBarW->healthBar->SetPercent(HP);
	}
}
