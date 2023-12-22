// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EchoHUD.generated.h"

/**
 * 
 */
class UEchoInterfaceComp;
class UWidgetMenu;
UCLASS()
class LEARNINGGAMEPLAY_API AEchoHUD : public AHUD
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UEchoInterface> echoInterfaceClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UWidgetMenu> menuWidgetClass;

	UPROPERTY()
		UEchoInterface* echoInterface;

	UPROPERTY()
		UWidgetMenu* menuWidget;

public :
	FORCEINLINE UEchoInterface* GetEchoInterface() const { return echoInterface; }

	FORCEINLINE UWidgetMenu* GetMenuWidget() const { return menuWidget; }



};
