// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EchoHUD.h"
#include "HUD/EchoInterface.h"
#include "HUD/EchoInterfaceComp.h"
#include "HUD/WidgetMenu.h"

void AEchoHUD::BeginPlay()
{
	Super::BeginPlay();

	echoInterface = CreateWidget<UEchoInterface>(GetWorld()->GetFirstPlayerController(), echoInterfaceClass);
	menuStartWidget = CreateWidget<UWidgetMenu>(GetWorld()->GetFirstPlayerController(), menuStartWidgetClass);
	//echoInterface->setKills();
	//echoInterface->AddToViewport();
	//menuStartWidget->AddToViewport(1);
}
