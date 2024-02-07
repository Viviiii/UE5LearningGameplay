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

void UEchoInterface::setPercentStamina(float stamina)
{
	if (staminaBar) {
		staminaBar->SetPercent(stamina);
	}
}

void UEchoInterface::displayDeath()
{
	if (Death) {
		Death->SetVisibility(ESlateVisibility::Visible);
	}
}

//void UEchoInterface::getHeal(float addHP)
//{
//	if (healthBar) {
//		healthBar->SetPercent(addHP);
//	}
//}

void UEchoInterface::getStamina(float addStamina)
{
	if (staminaBar) {
		staminaBar->SetPercent(addStamina);
	}
}

void UEchoInterface::showHUD()
{
	
	canvasPanel->SetVisibility(ESlateVisibility::Visible);
}

//void UEchoInterface::addCoins(int amount)
//{
//	if (coins) {
//		coinNbr = coinNbr + amount;
//		coins->SetText(FText::AsNumber(coinNbr));
//
//	}
//}

//void UEchoInterface::addKills()
//{
//	if (kills) {
//		killNbr++;
//		kills->SetText(FText::AsNumber(killNbr));
//
//	}
//}

void UEchoInterface::setFGKills()
{
	if (FGkills) {
		if (FGkills->GetVisibility() == ESlateVisibility::Hidden) {
			FGkills->SetVisibility(ESlateVisibility::Visible);
			FGkillNbr = -1;
		}
		FGkillNbr++;
		FGkills->SetText(FText::AsNumber(FGkillNbr));

	}
}

void UEchoInterface::setKills()
{
	if (kills) {
		if (kills->GetVisibility() == ESlateVisibility::Hidden) {
			kills->SetVisibility(ESlateVisibility::Visible);
			killNbr = -1;
		}
		killNbr++;
		kills->SetText(FText::AsNumber(killNbr));
	}
}

void UEchoInterface::setRound()
{
	if (roundNbr) {
		if (roundNbr->GetVisibility() == ESlateVisibility::Hidden) {
			roundNbr->SetVisibility(ESlateVisibility::Visible);
			roundNumber = -1;
		}
		roundNumber = 0;
		roundNumber ++;
		roundNbr->SetText(FText::AsNumber(roundNumber));
	}
}

void UEchoInterface::showEverything()
{
	healthBar->SetVisibility(ESlateVisibility::Hidden);
}

int UEchoInterface::getRound()
{
	return roundNumber;
}
