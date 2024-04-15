// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "EchoInterface.generated.h"



/**
 * 
 */

class UProgressBar;
class UImage;
class STextBlock;
class UCanvasPanel;
UCLASS()
class LEARNINGGAMEPLAY_API UEchoInterface : public UUserWidget
{
	GENERATED_BODY()

public : 

	UFUNCTION(BlueprintCallable)
	void showHUDSurvival();

	void setPercentHealth(float HP);

	void setPercentStamina(float stamina);

	void displayDeath();

	void getHeal(float addHP);

	void getStamina(float addStamina);


	void addKills();

	UFUNCTION(BlueprintCallable)
	void setKills();

	UFUNCTION(BlueprintCallable)
	void setKillsLogo();

	int getRound();


	UPROPERTY(BlueprintReadWrite)
		int killNbr;


private :
	UPROPERTY(meta = (BindWidget))
		UProgressBar* healthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* staminaBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Death;

		UTextBlock* Crotte;

	//UPROPERTY(meta = (BindWidget))
	UImage* killsLogo;


	//UPROPERTY(meta = (BindWidget))
		UCanvasPanel* canvasPanel;
	
	
};
