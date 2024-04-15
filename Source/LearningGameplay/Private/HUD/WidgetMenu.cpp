// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/WidgetMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HUD/WidgetSettings.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UWidgetMenu::showHUD()
{

	FInputModeUIOnly inputMode;
	
	APlayerController* playerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (canvasPanelMenu) {
		if (canvasPanelMenu->GetVisibility() == ESlateVisibility::Hidden) {
			//canvasPanelMenu->SetVisibility(ESlateVisibility::Visible);
			playerController->bShowMouseCursor = true;
			playerController->SetPause(true);
			inputMode.SetWidgetToFocus(this->TakeWidget());
			inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			playerController->SetInputMode(inputMode);
		}
		else {
			canvasPanelMenu->SetVisibility(ESlateVisibility::Hidden);
			playerController->bShowMouseCursor = false;
			playerController->SetPause(false);
		}
			
	}
	
}

void UWidgetMenu::playGame()
{
	APlayerController* playerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	FInputModeGameOnly inputMode;
	

	
	canvasPanelMenu->SetVisibility(ESlateVisibility::Hidden);
	playerController->bShowMouseCursor = false;
	playerController->SetPause(false);
	playerController->SetInputMode(inputMode);

}

void UWidgetMenu::quitGame()
{
	APlayerController* playerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	UKismetSystemLibrary::QuitGame(GetWorld(), playerController, EQuitPreference::Quit,true);
}

void UWidgetMenu::settingsMenu()
{
	settingsWidget = CreateWidget<UWidgetSettings>(GetWorld()->GetFirstPlayerController(), settingsWidgetClass);
	if (settingsWidget) {
		
		canvasPanelMenu->SetVisibility(ESlateVisibility::Hidden);
		
	}
	

}
