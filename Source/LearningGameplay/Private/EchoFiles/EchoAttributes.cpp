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
	//health = FMath::Clamp(health, 0.f, maxHealth);
	health = FMath::Clamp(health - Damage, 0.f, maxHealth);

}

float UEchoAttributes::getHealth()
{
	return health/maxHealth;
}

