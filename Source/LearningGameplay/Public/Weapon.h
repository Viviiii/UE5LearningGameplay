// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects.h"
#include "Sound/SoundWave.h"
#include "Weapon.generated.h"

/**
 * 
 */

class AEchoCharacter;
class USoundBase;
class UBoxComponent;

UCLASS()
class LEARNINGGAMEPLAY_API AWeapon : public AObjects
{
	GENERATED_BODY()


protected :

	class AEchoCharacter* echoCharacter;

		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public :
	AWeapon();
	void equip(USceneComponent* weap, FName socketName);

	void AttachMeshToComponent(USceneComponent* weap, const FName& socketName);

	void unEquip(USceneComponent* weap, FName socketName);
	void Sheathe(USceneComponent* weap, FName socketName);

private :
	
		AWeapon* weaponEquipped;

		UPROPERTY(EditAnywhere, Category = "Weapon Property")
	USoundBase* equipSound;

		UPROPERTY(EditAnywhere)
			UBoxComponent* Box;
	
};
