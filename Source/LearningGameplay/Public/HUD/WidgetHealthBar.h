// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "WidgetHealthBar.generated.h"

/**
 * 
 */

class UProgressBar;
UCLASS()
class LEARNINGGAMEPLAY_API UWidgetHealthBar : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(meta = (BindWidget))
		UProgressBar* healthBar;
	
};
