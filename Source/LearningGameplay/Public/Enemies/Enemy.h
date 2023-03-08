// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IHitInterface.h"
#include "Sound/SoundWave.h"
#include "Particles/ParticleSystem.h"
#include "Enemy.generated.h"

class USoundBase;
class UParticleSystem;

UCLASS()
class LEARNINGGAMEPLAY_API AEnemy : public ACharacter, public IIHitInterface
{
	GENERATED_BODY()

public:
	
	AEnemy();

protected:
	virtual void BeginPlay() override;

	/* Montages and sections played*/
	void PlayHitMontage(FName Section);

	void PlayIdleMontage();


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void getHit_Implementation(const FVector& impactPoint) override;

	void DirectionalHit(const FVector& impactPoint);

private :
	/* Animation montages*/

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Hit")
		UAnimMontage* hitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Idle")
		UAnimMontage* idleMontage;

	/*Sounds*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		USoundBase* hitSound;

	/*VFX*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		UParticleSystem* bloodEffect;

};
