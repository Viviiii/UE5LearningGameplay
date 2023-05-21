// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "EchoInterface.generated.h"


/**
 * 
 */

class UProgressBar;
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
	
	
};
