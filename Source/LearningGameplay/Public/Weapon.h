// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects.h"
#include "Weapon.generated.h"

/**
 * 
 */

class AEchoCharacter;
UCLASS()
class LEARNINGGAMEPLAY_API AWeapon : public AObjects
{
	GENERATED_BODY()

protected :

	class AEchoCharacter* echoCharacter;

		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
};
