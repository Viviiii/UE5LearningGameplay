// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EchoInterfaceComp.h"

void UEchoInterfaceComp::setPercentHealth(float HP)
{
	if (healthBarW == nullptr) {
		healthBarW = Cast<UEchoInterface>(GetUserWidgetObject());
	}

	if (healthBarW && healthBarW->healthBar) {
		healthBarW->healthBar->SetPercent(HP);
	}
}
