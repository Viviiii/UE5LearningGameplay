// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/IHitInterface.h"
#include "Sound/SoundWave.h"
#include "AIController.h"
#include "EchoFiles/EchoAttributes.h"
#include "EchoFiles/CharacterStateEnum.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystem.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseCharacter.h"
#include "HUD/HealthBar.h"
#include "ObjectFiles/Objects.h"
#include "Enemy.generated.h"

class USoundBase;
class UParticleSystem;
class UEchoAttributes;
class UWidgetComponent;
class UHealthBar;
class AAIController;
class UPawnSensingComponent;
class AObjects;

UCLASS()
class LEARNINGGAMEPLAY_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	/*Damage and attack functions */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	virtual void Destroyed() override;

	virtual void getHit_Implementation(const FVector& impactPoint, AActor* hitter) override;

	virtual void DirectionalHit(const FVector& impactPoint) override;

protected :

	/* Begin Play functions*/
	virtual void BeginPlay() override;

	void StartHealth();

	void SpawnDefaultWeapon();

	/* IA Navigation */

	void CheckCombatTarget();

	/*Navigation */
	bool isTargetInRange(AActor* target, double radius);

	void MoveToTarget(AActor* target);

	UFUNCTION()
		void patrolTimerFinished();

	AActor* choosingTarget();

	bool IsAttacking();

	bool IsChasing();

	bool IsAlive();

	bool IsOutsideAttackRadius();

	bool IsOutsideCombatRadius();

	bool bCanAttack();

	void ChaseTarget();

	void StartPatrolling();

	void LoseInterest();

	void startAttackTimer();

	UPROPERTY(BlueprintReadOnly, Category = "Death")
		TEnumAsByte<EDeathState> deathPose = EDeathState::ECS_Alive;

	FTimerHandle patrolTimer;

	UPROPERTY()
		AAIController* AIenemy;

	UPROPERTY(EditInstanceOnly, Category = " IA Navigation", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		AActor* targetPatrol;

	UPROPERTY(EditInstanceOnly, Category = " IA Navigation")
		TArray<AActor*> targetsPatrol;

	FTimerHandle attackTimer;

	UFUNCTION()
		void pawnSeen(APawn* pawn);

	UPROPERTY(EditAnywhere)
		TSubclassOf<AWeapon> weaponClass;

	UPROPERTY(EditAnywhere)
		UPawnSensingComponent* pawnSensing;

	void ShowHealth();

	void EnemyDeath();

	/* Montages and sections played*/
	virtual void PlayHitMontage(FName Section) override;

	virtual void PlayIdleMontage() override;

	/* Call attack montage*/
	virtual int32 PlayAttackMontage() override;

	virtual int32 PlayDeathMontage() override;

	/*virtual void ReduceHealth(float dmgAmount);*/

	/*Attacking */

	virtual void enableSwordCollision(ECollisionEnabled::Type CollisionEnabled) override;
	virtual void disableSwordCollision(ECollisionEnabled::Type CollisionEnabled) override;
	virtual void attackEnd() override;

	virtual void Attack() override;

private : 

	EEnemyState enemyState = EEnemyState::EES_Patrol;

	EActionState actionState = EActionState::EAS_Unoccupied;

	/* Chasing + attacks*/

	
	UPROPERTY(EditAnywhere)	
		double combatRadius = 1000.f;

	UPROPERTY(EditAnywhere)
		double attackRadius = 400.f;

	UPROPERTY(EditAnywhere)
		double patrolRadius = 5000.f;
};		
