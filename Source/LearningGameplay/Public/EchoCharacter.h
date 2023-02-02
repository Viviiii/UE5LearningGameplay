// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EchoCharacter.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;

UCLASS()
class LEARNINGGAMEPLAY_API AEchoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEchoCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private :
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* MainCharacter;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* Capsule;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
