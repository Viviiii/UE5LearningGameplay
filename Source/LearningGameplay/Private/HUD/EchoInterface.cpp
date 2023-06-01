// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EchoInterface.h"

void UEchoInterface::setPercentHealth(float HP)
{

	/*if (UProgressBar == nullptr) {
		healthBarEchoW = Cast<UEchoInterface>(GetUserWidgetObject());
	}*/

	if (healthBar) {
		healthBar->SetPercent(HP);
	}
}

void UEchoInterface::setPercentMana(float Mana)
{
	/*if (manaBarEchoW == nullptr) {
		manaBarEchoW = Cast<UEchoInterface>(GetUserWidgetObject());

	}*/
	if (manaBar) {
		manaBar->SetPercent(Mana);
	}
}

void UEchoInterface::addPotions()
{
	if (potions) {
		potionsNbr++;
		potions->SetText(FText::AsNumber(potionsNbr));

	}
}

void UEchoInterface::removePotions()
{
}

void UEchoInterface::addCoins(int amount)
{
	if (coins) {
		coinNbr = coinNbr + amount;
		coins->SetText(FText::AsNumber(coinNbr));

	}
}
