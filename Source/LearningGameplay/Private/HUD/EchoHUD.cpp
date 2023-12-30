// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EchoHUD.h"
#include "HUD/EchoInterfaceComp.h"
#include "HUD/WidgetMenu.h"

void AEchoHUD::BeginPlay()
{
	Super::BeginPlay();

	echoInterface = CreateWidget<UEchoInterface>(GetWorld()->GetFirstPlayerController(), echoInterfaceClass);
	menuWidget = CreateWidget<UWidgetMenu>(GetWorld()->GetFirstPlayerController(), menuWidgetClass);
	//echoInterface->AddToViewport();
}
