// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/WidgetMenu.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Kismet/GameplayStatics.h"

void UWidgetMenu::showHUD()
{
	if (canvasPanelMenu) {
		GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Red, FString("Menu"));
		canvasPanelMenu->SetVisibility(ESlateVisibility::Visible);
	}
	
}
