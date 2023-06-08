// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HUD/HealthBar.h"
#include "Interfaces/IHitInterface.h"
#include "ObjectFiles/Weapon.h"
#include "EchoFiles/EchoAttributes.h"
#include "BaseCharacter.generated.h"



class UEchoAttributes;
class UHealthBar;
class AWeapon;

UCLASS()
class LEARNINGGAMEPLAY_API ABaseCharacter : public ACharacter, public IIHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/* Characteristics + HUD Player*/
	UPROPERTY(EditAnywhere)
		UEchoAttributes* Attributes;

	UPROPERTY(VisibleAnywhere)
		UHealthBar* widgetHealth;

	/* Use weapon equipped*/

	UPROPERTY(VisibleInstanceOnly, Category = "Weapon")
		AWeapon* weaponEquipped;

	/* Variables for montage*/

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Hit")
		UAnimMontage* hitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Idle")
		UAnimMontage* idleMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Death")
		UAnimMontage* deathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Attack")
		UAnimMontage* attackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage Sections")
		TArray<FName> AttackMontageSections;

	UPROPERTY(EditAnywhere, Category = "Montage Sections")
		TArray<FName> DeathMontageSections;

	/*Sounds*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		USoundBase* hitSound;

	/*VFX*/
	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		UParticleSystem* bloodEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
		AActor* combatTarget;

	UPROPERTY(EditAnywhere, Category = "Enemy Hit")
		double WarpTargetDistance = 100.f;

	/* Attack and hit functions*/
	virtual void getHit_Implementation(const FVector& impactPoint, AActor* hitter) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	virtual void DirectionalHit(const FVector& impactPoint);

	virtual void ReduceHealth(float dmgAmount);


	/*Anim notify functions*/
	UFUNCTION(BlueprintCallable)
		virtual void attackEnd();

	UFUNCTION(BlueprintCallable)
		virtual void enableSwordCollision(ECollisionEnabled::Type CollisionEnabled);

	UFUNCTION(BlueprintCallable)
		virtual void disableSwordCollision(ECollisionEnabled::Type CollisionEnabled);

	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	/*Called for attacking (with montage)*/
	virtual void Attack();

	virtual void PlayMontageSection(UAnimMontage* montage, const FName& section);

	/* Choose a random section of a montage*/
	virtual int32 PlayRandomMontageSection(UAnimMontage* montage, TArray<FName> montageSections);


	/* Montages and sections played*/
	virtual void PlayHitMontage(FName Section);

	virtual int32 PlayDeathMontage();

	virtual int32 PlayAttackMontage();

	virtual void PlayIdleMontage();

	virtual void StopAttackMontage();

	virtual bool IsAlive();

	/* VFX & SFX*/

	virtual void PlayVFX(const FVector& impactPoint);

	virtual void PlaySound(const FVector& impactPoint);



};
