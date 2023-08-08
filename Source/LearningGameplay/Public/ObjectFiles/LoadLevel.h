// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectFiles/Objects.h"
//#include "ObjectFiles/Breakable.h"
#include "ObjectFiles/Potions.h"
#include "ObjectFiles/Weapon.h"
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

	/*UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AActor>> breakableClass;*/

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AActor>> potionsClass;

	void respawn(AEchoCharacter* echo);

	void respawnPaladins(int number);

	UFUNCTION()
		void newPaladin(int paladinNumber, int echoKillNbr);

	void respawnFG();

	UFUNCTION()
		void respawnRaptors(TArray<AEnemy*> fireGiantArray, int raptorsNbr);

	void roundOne();

	void roundTwo();

	void roundThree();

	void roundFour();

	void roundFive();

	void roundThreeBis();

	void nextRound();

	void spawnBonus();

	void dmgUp(AWeapon* weapon, float multiplier);

	void spawnBonusRandom();
	//FTimerHandle respawnTimer(int paladinNumber, int echoKillNbr, float delay);

	FTimerHandle respawnTimer;

	FTimerDelegate respawnParam;

	FTimerManager* MyTimerManager;

	void PlayVFX(FVector Location, UParticleSystem* FX);

	/*VFX*/
	UPROPERTY(EditAnywhere, Category = "Spawn FX")
		UParticleSystem* spawnEffect;

	int enemiesNumber=0;

	TArray<AEnemy*> paladinsTab;

	TArray<AEnemy*> raptorsTab;

	TArray<AEnemy*> FGTab;

	int raptorsNbr;

	int paladinsNbr;

	AWeapon* weapon;

public :

	AEnemy* newEnemy;

	AEchoCharacter* echo;
	
};
