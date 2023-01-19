// Fill out your copyright notice in the Description page of Project Settings.


#include "Shuriken.h"

#define DRAW_SPHERE_SINGLE_FRAME(Location) DrawDebugSphere(GetWorld(), Location, 30.f, 24, FColor::Green, false, -1.f);

// Sets default values
AShuriken::AShuriken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShuriken::BeginPlay()
{
	Super::BeginPlay();
	FVector Location = GetActorLocation();
	DRAW_SPHERE_SINGLE_FRAME(Location);
}

float AShuriken::movCalcul(float value)
{
	return /*Amplitude :*/ amplitude * FMath::Sin(runningTime * /*Speed :*/ speed);
}

// Called every frame
void AShuriken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	runningTime += DeltaTime;
	FVector Location = GetActorLocation();
	AddActorWorldOffset(FVector(0.f, 0.f, movCalcul(runningTime)));
	AddActorWorldRotation(FRotator(0.f, 45.f * DeltaTime, 0.f));



}

