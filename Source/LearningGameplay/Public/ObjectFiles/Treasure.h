// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects.h"
#include "HUD/EchoInterface.h"
#include "Treasure.generated.h"

/**
 * 
 */

class UEchoInterfaceComp;
UCLASS()

class LEARNINGGAMEPLAY_API ATreasure : public AObjects
{
	GENERATED_BODY()

private :
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, Category = "PickCoin")
		USoundBase* pickCoin;

	UPROPERTY(EditAnywhere, Category = "Gold")
		int32 Coin;

	/*UPROPERTY(EditAnywhere)
		UEchoInterfaceComp* echoWidget;*/

public :
	ATreasure();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
