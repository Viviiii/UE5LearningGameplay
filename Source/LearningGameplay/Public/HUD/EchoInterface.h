// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "EchoInterface.generated.h"



/**
 * 
 */

class UProgressBar;
class STextBlock;
UCLASS()
class LEARNINGGAMEPLAY_API UEchoInterface : public UUserWidget
{
	GENERATED_BODY()

public : 
	void setPercentHealth(float HP);

	void setPercentStamina(float stamina);

	void addPotions();

	void removePotions();

	void addCoins(int amount);

	UPROPERTY(BlueprintReadWrite)
		int potionsNbr;

	UPROPERTY(BlueprintReadWrite)
		int coinNbr;


private :
	UPROPERTY(meta = (BindWidget))
		UProgressBar* healthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* staminaBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* potions;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* coins;
	
	
};
