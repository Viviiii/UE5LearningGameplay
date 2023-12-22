// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/WidgetMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UWidgetMenu::showMenu()
{
	leaveTheGame->SetVisibility(ESlateVisibility::Visible);
	backToGame->SetVisibility(ESlateVisibility::Visible);
	backGround->SetVisibility(ESlateVisibility::Visible);
}
