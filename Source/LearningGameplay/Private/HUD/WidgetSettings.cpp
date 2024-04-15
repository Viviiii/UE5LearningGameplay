// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/WidgetSettings.h"
#include "HUD/EchoHUD.h"

void UWidgetSettings::backToMenuFunction()
{
	APlayerController* playerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	FInputModeGameOnly inputMode;

	if (canvasPanelSettings) {
		
		canvasPanelSettings->SetVisibility(ESlateVisibility::Hidden);		
	}
	
}
