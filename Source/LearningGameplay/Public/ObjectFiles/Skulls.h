// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectFiles/Objects.h"
#include "Skulls.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGGAMEPLAY_API ASkulls : public AObjects
{
	GENERATED_BODY()
	
private:
		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
