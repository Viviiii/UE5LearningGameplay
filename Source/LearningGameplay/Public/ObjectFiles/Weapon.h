// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects.h"
#include "Sound/SoundWave.h"
#include "NiagaraComponent.h"
#include "Weapon.generated.h"

/**
 * 
 */

class AEchoCharacter;
class USoundBase;
class UBoxComponent;
class UNiagaraComponent;

UCLASS()
class LEARNINGGAMEPLAY_API AWeapon : public AObjects
{
	GENERATED_BODY()


protected :
	virtual void BeginPlay() override;

	class AEchoCharacter* echoCharacter;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void createField(const FVector& location);
public :
	AWeapon();
	void equip(USceneComponent* weap, FName socketName,AActor* Owner, APawn* instigator) ;

	void AttachMeshToComponent(USceneComponent* weap, const FName& socketName);

	void unEquip(USceneComponent* weap, FName socketName);
	void Sheathe(USceneComponent* weap, FName socketName);

	FORCEINLINE UBoxComponent* getBoxCollision() {
		return Box;
	}

	TArray<AActor*> IgnoreActors;

private :
	
	AWeapon* weaponEquipped;

	UPROPERTY(EditAnywhere, Category = "Weapon Property")
	USoundBase* equipSound;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* BoxTraceEnd;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
		UNiagaraComponent* VFX;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
		float Damage = 20.f;
	
};
