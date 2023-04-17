// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/HealthBar.h"
#include "HUD/WidgetHealthBar.h"


void UHealthBar::setPercentHealth(float HP)
{
	if (healthBarW == nullptr) {
		healthBarW = Cast<UWidgetHealthBar>(GetUserWidgetObject());
	}
	
	if (healthBarW && healthBarW->healthBar) {
		healthBarW->healthBar->SetPercent(HP);
	}
}
