// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EchoInterface.h"
#include "EchoInterfaceComp.generated.h"



/**
 * 
 */
UCLASS()
class LEARNINGGAMEPLAY_API UEchoInterfaceComp : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	void setPercentHealth(float HP);

	void setPercentMana(float Mana);

	void addXP(float XP);

	void addPotions();

	void removePotions();

	void addCoins();

	UPROPERTY(BlueprintReadWrite)
		int potions;

	UPROPERTY(BlueprintReadWrite)
		int coin;

	UEchoInterface* potionsW;

	UEchoInterface* coinsW;

private:
		UEchoInterface* healthBarEchoW;

		UEchoInterface* manaBarEchoW;

		UEchoInterface* XPBarW;

		

		

};
