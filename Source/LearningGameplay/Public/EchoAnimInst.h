// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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


	UPROPERTY(BlueprintReadOnly, category = "Moves")
	class UCharacterMovementComponent* echoCharacterMove;

	UPROPERTY(BlueprintReadOnly, category = "Moves")
		float speed;

	UPROPERTY(BlueprintReadOnly, category = "Moves")
		bool isFalling;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float deltaTime);
	
};
