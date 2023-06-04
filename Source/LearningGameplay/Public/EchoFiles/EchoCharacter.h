// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterStateEnum.h"
#include "Interfaces/PickUpInterface.h"
#include "HUD/EchoInterfaceComp.h"
#include "ObjectFiles/Treasure.h"
#include "ObjectFiles/Potions.h"
#include "EchoCharacter.generated.h"



class USkeletalMeshComponent;
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AObjects;
class UAnimMontage;
class AWeapon;
class UEchoInterfaceComp;
class IPickUpInterface;

UCLASS()
class LEARNINGGAMEPLAY_API AEchoCharacter : public ABaseCharacter, public IPickUpInterface
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
	FORCEINLINE EActionState getActionState() {
		return actionState;
	}

	EActionState actionState = EActionState::EAS_Unoccupied;


	UPROPERTY(VisibleAnywhere)
		UEchoInterfaceComp* echoWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InteractAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	/** Ability1 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* Ability1Action;

	/** Ability2 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* Ability2Action;

	/** Draw/Sheathe Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* WeaponAction;

	/* SFX */
	UPROPERTY(EditAnywhere, Category = "Weapon Property")
		USoundBase* equipSound;

	/* Ability montage */
	UPROPERTY(EditDefaultsOnly, Category = "Montages | Abilities")
		UAnimMontage* abilitiesMontage;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/*Called for looking up*/
	void Look(const FInputActionValue& Value);

	/*Called for interacting*/
	void Interact();

	/*Called for interacting*/
	void Ability1();

	/*Anim notify functions*/

	UFUNCTION(BlueprintCallable)
		void disarmSword();

	UFUNCTION(BlueprintCallable)
		void hitReactionEnd();
	
	/*Draw/Sheathe weapon */
	void UnarmWeapon();

	void PlayUnarmMontage(FName sectionName);

	/* Shorts functions to check character+actionState*/
	bool canDraw();

	bool canSheathe();

	virtual void getHit_Implementation(const FVector& impactPoint) override;

	virtual void DirectionalHit(const FVector& impactPoint) override;

private :

	/*Inheritance test */

	/*Called for attacking (with montage)*/
	virtual void Attack() override;

	//virtual void PlayMontageSection(UAnimMontage* montage, const FName& section);

	///* Choose a random section of a montage*/
	//virtual int32 PlayRandomMontageSection(UAnimMontage* montage, TArray<FName> montageSections);

	/* Montages and sections played*/
	virtual void PlayHitMontage(FName Section) override;

	virtual int32 PlayDeathMontage() override;



	virtual int32 PlayAttackMontage() override;

	virtual void PlayIdleMontage() override;


	/* Overlapping objects*/
	UPROPERTY(VisibleInstanceOnly)
		AObjects* overlappedObjects;

	UEchoInterface* echoInterface;

	//Enum charac states

	ECharacterState characterState = ECharacterState::ECS_Unequipped;

	/* Animation montages*/

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Unarm")
		UAnimMontage* unarmMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Anim notify functions*/
	virtual void attackEnd() override;
	virtual void enableSwordCollision(ECollisionEnabled::Type CollisionEnabled) override;
	virtual void disableSwordCollision(ECollisionEnabled::Type CollisionEnabled) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	
	
	virtual void setOverlappingItem(AObjects* item) override;
	virtual void addCoins(ATreasure* treasure) override;
	virtual void addPotion(APotions* potion) override;

private:


	/* Used with camera*/
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FollowCamera;

	/* Groom components*/
	UPROPERTY(VisibleAnywhere, Category = "Hair")
		class UGroomComponent* Hair;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = "Hair")
		class UGroomComponent* Eyesbrows;

	void echoDeath();
};
