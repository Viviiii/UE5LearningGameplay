// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectFiles/Objects.h"
#include "Enemies/Enemy.h"
#include "EchoFiles/EchoCharacter.h"
#include "LoadLevel.generated.h"

class UParticleSystem;
/**
 * 
 */
UCLASS()
class LEARNINGGAMEPLAY_API ALoadLevel : public AObjects
{
	GENERATED_BODY()
	
private :
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AEnemy>> enemyClass;

	UFUNCTION()
		void respawn(AEchoCharacter* echo);

	void respawnPaladins();

	void respawnFG();

	FTimerHandle respawnTimer;
	
	FTimerDelegate respawnParam;

	void PlayVFX(FVector Location, UParticleSystem* FX);

	/*VFX*/
	UPROPERTY(EditAnywhere, Category = "Spawn FX")
		UParticleSystem* spawnEffect;

	int enemiesNumber=0;

	TArray<AEnemy*> paladinsTab;

	TArray<AEnemy*> raptorsTab;

	TArray<AEnemy*> FGTab;



public :

	AEnemy* newEnemy;

	AEchoCharacter* echo;
	
};
