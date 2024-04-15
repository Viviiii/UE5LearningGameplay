// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EchoInterface.h"

void UEchoInterface::showHUDSurvival()
{
	//Death->SetVisibility(ESlateVisibility::Visible);
	

}

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
		//Crotte->SetText(FText::FromString("Coucou caca "));
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


void UEchoInterface::addKills()
{
	killNbr++;
	
}

void  UEchoInterface::setKills()
{
	/*if (killsTxt) {
		
		killNbr++;
		killsTxt->SetText(FText::AsNumber(killNbr));
		
	}*/
}

void UEchoInterface::setKillsLogo()
{
	if (killsLogo) {
		killsLogo->SetVisibility(ESlateVisibility::Visible);
	}
	
}
