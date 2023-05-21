// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/EchoInterface.h"
#include "HUD/EchoInterfaceComp.h"
#include "HUD/WidgetHealthBar.h"
#include "Components/ProgressBar.h"

void UEchoInterfaceComp::setPercentHealth(float HP)
{
	
	if (healthBarEchoW == nullptr) {
		healthBarEchoW = Cast<UEchoInterface>(GetUserWidgetObject());
	}

	if (healthBarEchoW && healthBarEchoW->healthBar) {
		healthBarEchoW->healthBar->SetPercent(HP);
	}
}

void UEchoInterfaceComp::setPercentMana(float Mana)
{
	if (manaBarEchoW == nullptr) {
		manaBarEchoW = Cast<UEchoInterface>(GetUserWidgetObject());
		
	}
	if (manaBarEchoW && manaBarEchoW->manaBar) {
		manaBarEchoW->manaBar->SetPercent(Mana);
	}
}

void UEchoInterfaceComp::addXP(float XP)
{
	if (XPBarW == nullptr) {
		XPBarW = Cast<UEchoInterface>(GetUserWidgetObject());

	}
	if (XPBarW && XPBarW->XPBar) {
		XPBarW->XPBar->SetPercent(XP);
	}
}
