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

void UEchoInterfaceComp::addPotions()
{
	if (potionsW == nullptr) {
		potionsW = Cast<UEchoInterface>(GetUserWidgetObject());
		potions = 0;

	}
	if (potionsW && potionsW->potions) {
		potions++;
		potionsW->potions->SetText(FText::AsNumber(potions));
		
	}
}

void UEchoInterfaceComp::removePotions()
{
}

void UEchoInterfaceComp::addCoins()
{
	if (coinsW == nullptr) {
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString("NOOOOOOOOOOOOOOOO"));
		coinsW = Cast<UEchoInterface>(GetUserWidgetObject());
		coin = 0;

	}
	if (coinsW && coinsW->coins) {
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, FString("Almost there"));
		coin = coin + 5 ;
		coinsW->coins->SetText(FText::AsNumber(coin));

	}
}
