// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterStateEnum.h"
#include "Interfaces/PickUpInterface.h"
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
class UWidgetMenu;

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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EActionState getActionState() {
		return actionState;
	}

	FORCEINLINE TEnumAsByte<EDeathState> getDeathState() {
		return deathPose;
	}

	UPROPERTY(VisibleAnywhere)
		UWidgetMenu* menuWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UEchoInterface> echoInterfaceClass;

	virtual void setKillNumber() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitOverlay(APlayerController* PlayerController);

	void InitOverlayRound(APlayerController* PlayerController);

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

	/** Draw/Sheathe Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* DodgeAction;

	/** Menu Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MenuAction;

	///* SFX */
	//UPROPERTY(EditAnywhere, Category = "Sound hurt")
	//	USoundBase* hurtSound;

	/* Ability montage */
	UPROPERTY(EditDefaultsOnly, Category = "Montages | Abilities")
		UAnimMontage* abilitiesMontage;

	/* Dodge montage */
	UPROPERTY(EditDefaultsOnly, Category = "Montages | Dodge")
		UAnimMontage* dodgeMontage;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/*Called for looking up*/
	void Look(const FInputActionValue& Value);

	/*Called for interacting*/
	void Interact();

	/*Called for ability1*/
	void Ability1();

	/*Called for dodging*/
	void Dodge();

	/*Called for menu*/
	void Menu();

	void PlayDodgeMontage();

	/*Anim notify functions*/

	UFUNCTION(BlueprintCallable)
		void disarmSword();

	UFUNCTION(BlueprintCallable)
		void hitReactionEnd();

	UFUNCTION(BlueprintCallable)
		void dodgeEnd();

	void StopDodgeMontage();
	
	/*Draw/Sheathe weapon */
	void UnarmWeapon();

	void PlayUnarmMontage(FName sectionName);

	/* Shorts functions to check character+actionState*/
	bool canDraw();

	bool canSheathe();

	/*UPROPERTY(BlueprintReadWrite)
		int killNumber;*/

	//Sint getKillNumber();

	

	virtual void getHit_Implementation(const FVector& impactPoint, AActor* hitter) override;

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

	virtual int32 PlayIdleMontage() override;


	/* Overlapping objects*/
	UPROPERTY(VisibleInstanceOnly)
		AObjects* overlappedObjects;

	/*UEchoInterface* echoInterface;*/

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
	//virtual void addCoins(ATreasure* treasure) override;
	virtual void getHeal(APotions* potion) override;
	virtual void getStamina(APotions* potion) override;
	virtual void addKills(ASkulls* skull) override;

	UFUNCTION(BlueprintCallable)
	int getKillNumber();

	UFUNCTION(BlueprintCallable)
	float getHeal();

	UFUNCTION(BlueprintCallable)
	float getStamina();

	/*Sounds*/
	UPROPERTY(EditAnywhere, Category = "Game Music")
		USoundBase* musicGame;

	UPROPERTY(BlueprintReadOnly)
		float maxSpeed;


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
