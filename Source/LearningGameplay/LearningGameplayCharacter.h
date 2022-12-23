// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LearningGameplayCharacter.generated.h"


UCLASS(config=Game)
class ALearningGameplayCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Basic Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* BasicAttackAction;

public:
	ALearningGameplayCharacter();
	

protected:

	/** Health of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float health;

	/** Endurance of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float endurance;

	/** Strength of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float strength;

	/** Level of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		int level;

	/** XP of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		int XP;

	/** Speed of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float speed;

	/** Sprint speed of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float sprintSpeed;


	/** XP of the player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool nextLevel;

	/** Activate animation sprint */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool isSprinting;

	/** Activate basic attack */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool basicAttack;

	/** ENEMY PROPERTIES **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
		float enemyHealth;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	//Called for start sprinting
	void StartSprinting();

	//Called for stop sprinting
	void StopSprinting();

	//Called to use BasicAttack
	void startBasicAttack();

	// Called to stop BasicAttack
		void endBasicAttack();

	UFUNCTION(BlueprintCallable)
		void takeDamage(float amount);

	UFUNCTION(BlueprintCallable)
		float getHealthPercent(float hp);

	UFUNCTION(BlueprintCallable)
		float getEndurancePercent(float end);

	UFUNCTION(BlueprintCallable)
		void levelUP(float experience);



	UFUNCTION(BlueprintCallable)
		void healing(float amount);

	UFUNCTION(BlueprintCallable)
		void takeDamageEnemy(float strengh);

	UFUNCTION(BlueprintCallable)
		bool enemyDead(float enemy);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};


