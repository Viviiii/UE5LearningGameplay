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

public:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* healthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* manaBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* XPBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* potions;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* coins;
	
	
};
