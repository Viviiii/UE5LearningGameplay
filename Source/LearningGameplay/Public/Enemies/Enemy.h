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
class AEchoCharacter;
class ASkulls;

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

	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemy> enemyClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AObjects> skullClass;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EEnemyState getEnemyState() {
			return enemyState;
		}
	void MoveToRandomLocation();

	/* To improve */
	bool IsAlive();

	int enemyNbr;

	int getEnemyNbr();

	void setEnemyNbr(int value);

	AEchoCharacter* echo;

	/*VFX*/
	UPROPERTY(EditAnywhere, Category = "Enemy Spawn")
		UParticleSystem* spawnFX;

	AWeapon* getWeapon();

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

	AActor* choosingTarget();

	bool IsAttacking();

	bool IsChasing();

	bool IsOutsideAttackRadius();

	bool IsOutsideCombatRadius();

	bool bCanAttack();

	UFUNCTION(BlueprintCallable)
	void ChaseTarget();

	void StartPatrolling();

	void LoseInterest();

	void startAttackTimer();

	void patrolTimerFinished();

	void respawnEnemyTimer();

	/*UPROPERTY(BlueprintReadOnly, Category = "Death")
		TEnumAsByte<EDeathState> deathPose = EDeathState::ECS_Alive;*/

	UPROPERTY(BlueprintReadOnly, Category = "Idle")
		TEnumAsByte<EEnemyIdleState> idlePose = EEnemyIdleState::EEIS_Idle1;

	UPROPERTY()
		AAIController* AIenemy;
	

	UPROPERTY(EditInstanceOnly, Category = " IA Navigation", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		AActor* targetPatrol;

	UPROPERTY(EditInstanceOnly, Category = " IA Navigation")
		TArray<AActor*> targetsPatrol;

	FTimerHandle patrolTimer;

	FTimerHandle attackTimer;

	FTimerHandle respawnTimer;

	FTimerHandle randomPatrolTimer;

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

	virtual int32 PlayIdleMontage() override;

	/* Call attack montage*/
	virtual int32 PlayAttackMontage() override;

	virtual int32 PlayDeathMontage() override;

	void PlaySpawnMontage();

	/*virtual void ReduceHealth(float dmgAmount);*/

	/*Attacking */

	virtual void enableSwordCollision(ECollisionEnabled::Type CollisionEnabled) override;
	virtual void disableSwordCollision(ECollisionEnabled::Type CollisionEnabled) override;
	virtual void attackEnd() override;

	virtual void Attack() override;

	UPROPERTY(BlueprintReadOnly)
		float maxSpeed;

	///*Sounds*/
	//UPROPERTY(EditAnywhere, Category = "Enemy Hit")
	//	USoundBase* hitSound;

	///*VFX*/
	//UPROPERTY(EditAnywhere, Category = "Enemy Hit")
	//	UParticleSystem* bloodEffect;

private : 

	EEnemyState enemyState = EEnemyState::EES_Patrol;

	EActionState actionState = EActionState::EAS_Unoccupied;

	/* Chasing + attacks*/

	UPROPERTY(EditAnywhere)
		double combatRadius = 500.f;

	UPROPERTY(EditAnywhere)
		double attackRadius = 350.f;

	UPROPERTY(EditAnywhere)
		double patrolRadius = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float attackIntMin = 3.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float attackIntMax = 5.5f;


	UFUNCTION(BlueprintCallable)
		void destroyActor();

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Spawn")
		UAnimMontage* spawnMontage;


};		
