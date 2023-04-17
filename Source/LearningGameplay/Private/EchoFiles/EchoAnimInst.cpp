// Fill out your copyright notice in the Description page of Project Settings.

#include "EchoFiles/EchoAnimInst.h"
#include "EchoFiles/EchoCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UEchoAnimInst::NativeInitializeAnimation() {

	Super::NativeInitializeAnimation();
	echoCharacter = Cast<AEchoCharacter>(TryGetPawnOwner());
		if (echoCharacter) {
			echoCharacterMove = echoCharacter->GetCharacterMovement();
		}

}

void UEchoAnimInst::NativeUpdateAnimation(float deltaTime) {
	Super::NativeUpdateAnimation(deltaTime);
	if (echoCharacterMove) {
		speed = UKismetMathLibrary::VSizeXY(echoCharacterMove->Velocity);
		isFalling = echoCharacterMove->IsFalling();
		characterState = echoCharacter->getCharacterState();
	}
	
}