// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMenu.generated.h"


class UButton;
class UImage;
/**
 * 
 */
UCLASS()
class LEARNINGGAMEPLAY_API UWidgetMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void showMenu();

private: 
	UPROPERTY(meta = (BindWidget))
		UButton* leaveTheGame;

	UPROPERTY(meta = (BindWidget))
		UButton* backToGame;

	UPROPERTY(meta = (BindWidget))
		UImage* backGround;
};
