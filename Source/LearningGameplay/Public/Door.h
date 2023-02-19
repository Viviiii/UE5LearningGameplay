// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGGAMEPLAY_API ADoor : public AObjects
{
	GENERATED_BODY()

private : 
	virtual void BeginPlay();
	bool open = false;

protected :
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public :
	void doorOpening();
	
};
