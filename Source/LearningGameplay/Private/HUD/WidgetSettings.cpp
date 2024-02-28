// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/WidgetSettings.h"
#include "HUD/EchoHUD.h"

void UWidgetSettings::backToMenuFunction()
{
	APlayerController* playerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	FInputModeGameOnly inputMode;

	if (canvasPanelSettings) {
		GEngine->AddOnScreenDebugMessage(4, 1.5f, FColor::Red, FString("backToMenuFunction"));
		canvasPanelSettings->SetVisibility(ESlateVisibility::Hidden);		
	}
	
}

void UWidgetSettings::showHUD()
{
	AddToViewport(2);
	if (canvasPanelSettings != nullptr) {
		GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Red, FString("ShowHUD"));

		AddToViewport(2);
		canvasPanelSettings->SetVisibility(ESlateVisibility::Visible);
	}
	
}
