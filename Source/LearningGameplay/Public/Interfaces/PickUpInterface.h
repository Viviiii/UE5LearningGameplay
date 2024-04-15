// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "ObjectFiles/Objects.h"
#include "PickUpInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickUpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEARNINGGAMEPLAY_API IPickUpInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void setOverlappingItem(class AObjects* item);
	virtual void addCoins(class ATreasure* treasure);
	virtual void getHeal(class APotions* potion);
	virtual void addKills(class ASkulls* skull);
	virtual void getStamina(class APotions* potion);
};
