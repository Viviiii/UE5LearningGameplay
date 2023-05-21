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

private:
		UEchoInterface* healthBarEchoW;

		UEchoInterface* manaBarEchoW;

		UEchoInterface* XPBarW;

};
