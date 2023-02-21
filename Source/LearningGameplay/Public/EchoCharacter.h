// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterStateEnum.h"
#include "EchoCharacter.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AObjects;
class UAnimMontage;

UCLASS()
class LEARNINGGAMEPLAY_API AEchoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEchoCharacter();

	FORCEINLINE void setOverlappingObject(AObjects* object) {
		overlappedObjects = object;
	}
	FORCEINLINE ECharacterState getCharacterState() {
		return characterState;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/* Called for movement input*/
	void MoveRight(const FInputActionValue& Value);

	/*Called for looking up*/
	void Look(const FInputActionValue& Value);

	/*Called for interacting*/
	void Interact();

	void PlayAttackMontage();

	/*Called for attacking (with montage)*/
	void Attack();

	/*Anim notify functions*/
	UFUNCTION(BlueprintCallable)
		void attackEnd();

private :
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Hair")
		class UGroomComponent* Hair;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = "Hair")
		class UGroomComponent* Eyesbrows;

	UPROPERTY(VisibleInstanceOnly)
		AObjects* overlappedObjects;

	//Enum charac states

	ECharacterState characterState = ECharacterState::ECS_Unequipped;

	EActionState actionState = EActionState::ECS_Unoccupied;



	/* Animation montages*/

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Attack")
	UAnimMontage* attackMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool interact;
	

};
