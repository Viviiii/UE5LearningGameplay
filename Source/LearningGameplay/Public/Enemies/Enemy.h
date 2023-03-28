// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IHitInterface.h"
#include "Sound/SoundWave.h"
#include "AIController.h"
#include "EchoFiles/EchoAttributes.h"
#include "EchoFiles/CharacterStateEnum.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystem.h"
#include "HUD/HealthBar.h"
#include "Enemy.generated.h"

class USoundBase;
class UParticleSystem;
class UEchoAttributes;
class UWidgetComponent;
class UHealthBar;
class AAIController;

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

	void PlayDeathMontage();

	void PlayIdleMontage();

	UPROPERTY(BlueprintReadOnly)
		EDeathState deathState = EDeathState::ECS_Alive;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void getHit_Implementation(const FVector& impactPoint) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);


	void DirectionalHit(const FVector& impactPoint);

private :
	UPROPERTY(EditAnywhere)
		UEchoAttributes* Attributes;

	UPROPERTY(VisibleAnywhere)
		UHealthBar* widgetHealth;



	/* Animation montages*/

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Hit")
		UAnimMontage* hitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Idle")
		UAnimMontage* idleMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Death")
		UAnimMontage* deathMontage;

	/*Sounds*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		USoundBase* hitSound;

	/*VFX*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		UParticleSystem* bloodEffect;

	UPROPERTY()
		AActor* combatTarget;

	UPROPERTY(EditAnywhere)
		double combatRadius = 500.f;

	UPROPERTY()
		AAIController* AIenemy;

	/*Navigation */
	UPROPERTY(EditInstanceOnly, Category =" IA Navigation")
		AActor* targetPatrol;

	UPROPERTY(EditInstanceOnly, Category = " IA Navigation")
		TArray<AActor*> targetsPatrol;

};		
