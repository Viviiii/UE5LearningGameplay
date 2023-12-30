// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "WidgetMenu.generated.h"


class UButton;
class UImage;
class STextBlock;
class UProgressBar;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class LEARNINGGAMEPLAY_API UWidgetMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void showHUD();

	

private: 
	
	UPROPERTY(meta = (BindWidget))
	UButton* leaveTheGame;


	UPROPERTY(meta = (BindWidget))
	UImage* backGround;

	UPROPERTY(meta = (BindWidget))
		UButton* backToGame;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* canvasPanelMenu;

};
