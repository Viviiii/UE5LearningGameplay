// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Arena.h"

void AArena::BeginPlay()
{
	
}

void AArena::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector spawnLocation = FVector(-15750, -2520, 630);
	AEnemy* newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass, spawnLocation, GetActorRotation());

}
