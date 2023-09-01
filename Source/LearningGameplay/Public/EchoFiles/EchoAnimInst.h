// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EchoCharacter.h"
#include "EchoAnimInst.generated.h"

/**
 * 
 */

class UCharacterMovementComponent;

UCLASS()
class LEARNINGGAMEPLAY_API UEchoAnimInst : public UAnimInstance
{
	GENERATED_BODY()

public :

	UPROPERTY(BlueprintReadOnly)
	class AEchoCharacter* echoCharacter;


	UPROPERTY(BlueprintReadOnly, category = "Character | CharacterMovement")
	class UCharacterMovementComponent* echoCharacterMove;

	UPROPERTY(BlueprintReadOnly, category = "Character | CharacterMovement")
		float speed;

	UPROPERTY(BlueprintReadOnly, category = "Character | CharacterMovement")
		bool isFalling;

	UPROPERTY(BlueprintReadOnly, category = "Character | CharacterState")
	ECharacterState characterState;

	UPROPERTY(BlueprintReadOnly, category = "Character | ActionState")
	EActionState actionState;

	UPROPERTY(BlueprintReadOnly, category = "Character | DeathState")
	TEnumAsByte<EDeathState> deathPose;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float deltaTime);
	
};
