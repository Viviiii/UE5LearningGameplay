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
#include "Perception/PawnSensingComponent.h"
#include "HUD/HealthBar.h"
#include "Enemy.generated.h"

class USoundBase;
class UParticleSystem;
class UEchoAttributes;
class UWidgetComponent;
class UHealthBar;
class AAIController;
class UPawnSensingComponent;

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

	void PlayAttackMontage();

	UPROPERTY(BlueprintReadOnly)
		EDeathState deathState = EDeathState::ECS_Alive;

	/*Navigation */

	bool isTargetInRange(AActor* target, double radius);

	void MoveToTarget(AActor* target);

	UFUNCTION()
	void patrolTimerFinished();

	AActor* choosingTarget();


public:	
	virtual void Tick(float DeltaTime) override;

	/*Navigation */
	UFUNCTION()
	void CheckPatrolTarget();

	void CheckCombatTarget();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void getHit_Implementation(const FVector& impactPoint) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
	void pawnSeen(APawn* pawn);

	void DirectionalHit(const FVector& impactPoint);

	EEnemyState enemyState = EEnemyState::EES_Patrol;

private :
	UPROPERTY(EditAnywhere)
		UEchoAttributes* Attributes;

	UPROPERTY(VisibleAnywhere)
		UHealthBar* widgetHealth;

	FTimerHandle patrolTimer;


	/* Animation montages*/

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Hit")
		UAnimMontage* hitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Idle")
		UAnimMontage* idleMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Death")
		UAnimMontage* deathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Attack")
		UAnimMontage* attackMontage;


	/*Sounds*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		USoundBase* hitSound;

	/*VFX*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		UParticleSystem* bloodEffect;



	/*Navigation */



	UPROPERTY()
		AAIController* AIenemy;

	UPROPERTY(EditInstanceOnly, Category =" IA Navigation", BlueprintReadWrite, meta =(AllowPrivateAccess = "true"))
		AActor* targetPatrol;

	UPROPERTY(EditInstanceOnly, Category = " IA Navigation")
		TArray<AActor*> targetsPatrol;

	/* Chasing + attacks*/
	UPROPERTY(EditInstanceOnly, Category = " IA Navigation")
		AActor* combatTarget;

	UPROPERTY(EditAnywhere)
		double combatRadius = 1200.f;

	UPROPERTY(EditAnywhere)
		double attackRadius = 150.f;

	UPROPERTY(EditAnywhere)
		double patrolRadius = 5000.f;

	UPROPERTY(EditAnywhere)
		UPawnSensingComponent* pawnSensing;

};		
