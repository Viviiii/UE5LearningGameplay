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

private :
	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		UActorComponent* health;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		UActorComponent* maxHealth;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		UActorComponent* gold;

	UPROPERTY(EditAnywhere, Category = "Echo Attributes")
		UActorComponent* level;
		
};
