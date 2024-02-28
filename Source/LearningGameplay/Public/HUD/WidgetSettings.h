// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "WidgetSettings.generated.h"

/**
 * 
 */

class UCanvasPanel;
UCLASS()
class LEARNINGGAMEPLAY_API UWidgetSettings : public UUserWidget
{
	GENERATED_BODY()
	
public :
	UCanvasPanel* canvasPanelSettings;

	UFUNCTION(BlueprintCallable)
	void backToMenuFunction();

	UFUNCTION(BlueprintCallable)
	void showHUD();
private:

	UWidget* widgetMenu;

};
