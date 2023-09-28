// Fill out your copyright notice in the Description page of Project Settings.


#include "EchoFiles/EchoAttributes.h"

// Sets default values for this component's properties
UEchoAttributes::UEchoAttributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEchoAttributes::BeginPlay()
{
	Super::BeginPlay();
	name = FName("Raptor");
	// ...
	
}


// Called every frame
void UEchoAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEchoAttributes::ReceiveDamage(float Damage)
{
	health = FMath::Clamp(health - Damage, 0.f, maxHealth);
}

void UEchoAttributes::useStamina(float staminaAmount)
{
	stamina = FMath::Clamp(stamina - staminaAmount, 0.f, maxStamina);
}

float UEchoAttributes::getHealth()
{

	return health/maxHealth;
}

float UEchoAttributes::getStamina()
{
	return stamina / maxStamina;
}

void UEchoAttributes::setStamina(float staminaAmount)
{
	stamina += staminaAmount;
}

bool UEchoAttributes::isAlive()
{
	return health >0.f;
}

int UEchoAttributes::getKillNumber()
{
	return killNumber;
}

void UEchoAttributes::setKillFG()
{
	killFG++;
}

int UEchoAttributes::getKillFG()
{
	return killFG;
}

FName UEchoAttributes::getName()
{
	return name;
}

void UEchoAttributes::setName(FName newName)
{
	name = newName;
}

void UEchoAttributes::setHealth(float HP)
{
	health = FMath::Clamp(health + HP, 0.f, maxHealth);
	//health = HP;
}



