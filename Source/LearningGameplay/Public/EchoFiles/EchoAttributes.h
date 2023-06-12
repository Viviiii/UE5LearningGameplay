// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EchoAttributes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGGAMEPLAY_API UEchoAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	

	UEchoAttributes();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReceiveDamage(float Damage);

	void useStamina(float staminaAmount);

	float getHealth();

	float getStamina();

	void setStamina(float staminaAmount);

	bool isAlive();

private :
	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		float health;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		float maxHealth;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		int gold;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		int level;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		float stamina;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		float maxStamina;
		
};
