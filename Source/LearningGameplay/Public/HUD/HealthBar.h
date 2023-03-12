// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "WidgetHealthBar.h"
#include "HealthBar.generated.h"


/**
 * 
 */
UCLASS()
class LEARNINGGAMEPLAY_API UHealthBar : public UWidgetComponent
{
	GENERATED_BODY()
public: 
	void setPercentHealth(float HP);
private: 
	UWidgetHealthBar* healthBarW;
};
