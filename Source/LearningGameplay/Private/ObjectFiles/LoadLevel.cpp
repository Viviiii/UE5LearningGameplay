// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/LoadLevel.h"
#include "Kismet/GameplayStatics.h"

/**/
void ALoadLevel::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	echo = Cast<AEchoCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	FVector changeLocation = FVector(
		FMath::RandRange(-18770, -13140),
		FMath::RandRange(-770, -6450),
		900);

	if (OtherActor == echo) {
		SetActorLocation(changeLocation);
		nextRound();
	}
	
	
}

//Respawn x paladins depending on the round
void ALoadLevel::respawnPaladins(int paladinNumber)
{
	spawnBonusRandom();
	//Spawn all paladins depending on round
	respawnParam = FTimerDelegate::CreateUObject(this, &ALoadLevel::newPaladin, paladinNumber, echo->getKillNumber());
	//respawnTimer(paladinNumber, echo->getKillNumber(), FMath::RandRange(2.5f, 10.f));
	GetWorld()->GetTimerManager().SetTimer(respawnTimer, respawnParam, FMath::RandRange(5.f, 12.f), true, 0.1f);
	//GetWorld()->GetTimerManager().SetTimer(respawnTimer, this, &ALoadLevel::newPaladin, FMath::RandRange(2.5f, 10.f), true, 0.1f);
}

void ALoadLevel::newPaladin(int paladinNumber, int echoKillNumber)
{
	//Add VFX ?
	
	/*FVector spawnLocation = FVector(
		FMath::RandRange(-18800.f, -13400.f),
		FMath::RandRange(- 1700.f, -6550.f),
		630);*/

	FVector spawnLocation = FVector(
		FMath::RandRange(9625.f, 15505.f),
		FMath::RandRange(294.f, 7624.f),
		206);

	if (paladinsTab.Num() < paladinNumber) {
		newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[0], spawnLocation, GetActorRotation());
		paladinsTab.Add(newEnemy);
		/* Damage increase just for one round = fourth round*/
		/*if (echo->echoInterface->getRound() == 4) {
		weapon = newEnemy->getWeapon();
		weapon->setDmg(5.3);
		}*/

		
	}
	else if (echo->getKillNumber() == paladinNumber + echoKillNumber) {
		GetWorld()->GetTimerManager().ClearTimer(respawnTimer);
		paladinsTab.Empty();
		respawnFG();
	}
	
}

void ALoadLevel::respawnFG()
{
	FVector spawnLocationFG = FVector(
				12230.f,
				3770.f,
				278.f);

	newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[1], spawnLocationFG, GetActorRotation());
	FGTab.Add(newEnemy);
	if (newEnemy->spawnFX) {
		PlayVFX(spawnLocationFG, newEnemy->spawnFX);
	}
	/*if (echo->echoInterface->getRound() % 5 == 0) {
		newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[1], spawnLocationFG, GetActorRotation());
		FGTab.Add(newEnemy);
		if (newEnemy->spawnFX) {
			PlayVFX(spawnLocationFG, newEnemy->spawnFX);
		}
	}*/
	newEnemy = nullptr;
	respawnParam = FTimerDelegate::CreateUObject(this, &ALoadLevel::respawnRaptors, FGTab, raptorsNbr);
	GetWorld()->GetTimerManager().SetTimer(respawnTimer, respawnParam, FMath::RandRange(20.f, 40.f), true, 0.1f);
	
	/* Just in case*/
	//respawnParam.BindUFunction(this, FName("respawnRaptors"), FGTab);
	//GetWorld()->GetTimerManager().SetTimer(respawnTimer, this, &ALoadLevel::respawnRaptors, FMath::RandRange(20.f, 45.f), true, 0.1f);
}

void ALoadLevel::respawnRaptors(TArray<AEnemy*> FireGiantArray, int raptors)
{
	/* Checking if FG are dead*/
	for (int i = 0; i < FireGiantArray.Num() - 1; i++) {
		/* If yes, go next round*/
		if (FireGiantArray[i]->Attributes->getHealth() == 0) {
			GetWorld()->GetTimerManager().ClearTimer(respawnTimer);
			FGTab.Empty();
			nextRound();

		}
		/* If not, still respawn raptors*/
		else {
			break;
		}
	}
		spawnBonusRandom();
		FVector spawnLocationR = FVector(
			12660,
			3550,
			298);
		for (int i = 0; i < raptors; i++) {
			newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());
		}
		
		/*if (newEnemy != nullptr) {
			if (newEnemy->spawnFX) {

				PlayVFX(spawnLocationR, newEnemy->spawnFX);
			}
		}*/
}

void ALoadLevel::roundOne()
{
	//Call the respawn
	paladinsNbr = 5;
	raptorsNbr = 3;
	respawnPaladins(paladinsNbr);
	
}

void ALoadLevel::roundTwo()
{	
	//Increase number of paladins + minions
	paladinsNbr = 7;
	raptorsNbr = 3;
	respawnPaladins(paladinsNbr);
}

void ALoadLevel::roundThree()
{
	//Increase number of paladins + minions
	paladinsNbr = 10;
	raptorsNbr = 4;
	respawnPaladins(paladinsNbr);
}

void ALoadLevel::roundFour()
{
	//Increase number of paladins + minions + dmg
	paladinsNbr = 13;
	raptorsNbr = 4;
	//dmgUp(weapon, 1.3f);
	respawnPaladins(paladinsNbr);
}

void ALoadLevel::roundFive()
{
	//Increase number of FG = *2
	paladinsNbr = 0;
	raptorsNbr = 0;
	respawnPaladins(paladinsNbr);
}

void ALoadLevel::nextRound()
{
	/*if (echo->Attributes->getKillFG() == 0) {
		spawnBonus();
		roundOne();
	}
	else if (echo->Attributes->getKillFG() == 1) {
		spawnBonus();
		echo->echoInterface->setRound();
		roundTwo();

	}
	else if (echo->Attributes->getKillFG() == 2) {
		spawnBonus();
		echo->echoInterface->setRound();
		roundThree();
	}
	else if (echo->Attributes->getKillFG() == 3) {
		spawnBonus();
		echo->echoInterface->setRound();
		roundFour();
	}
	else if (echo->Attributes->getKillFG() == 4) {
		spawnBonus();
		echo->echoInterface->setRound();
		roundFive();
	}*/
}

void ALoadLevel::spawnBonus()
{
	
	for (int i = 0; i < 4; i++) {
		FVector spawnLocation = FVector(
			FMath::RandRange(9351.f, 15491.f),
			FMath::RandRange(1880.f, 7010.f),
			300.f);
		GetWorld()->SpawnActor<APotions>(potionsClass[0], spawnLocation, GetActorRotation());
		
	}
	//GetWorld()->SpawnActor<APotions>(potionsClass[0], spawnLocation, GetActorRotation());
}

void ALoadLevel::dmgUp(AWeapon* weap, float multiplier)
{
	if (weap) {
		weap->setDmg(multiplier);
	}
	
}

void ALoadLevel::spawnBonusRandom()
{
	int rand = FMath::RandRange(0, 1);
	if (rand == 1) {
		for (int i = 0; i < 4; i++) {
			FVector spawnLocation = FVector(
				FMath::RandRange(9351.f, 15491.f),
				FMath::RandRange(1880.f, 7010.f),
				300.f);
			GetWorld()->SpawnActor<APotions>(potionsClass[0], spawnLocation, GetActorRotation());
			GetWorld()->SpawnActor<APotions>(potionsClass[1], spawnLocation, GetActorRotation());
		}
	}
}

void ALoadLevel::respawn(AEchoCharacter* echoCharac)
{
}

void ALoadLevel::PlayVFX(FVector Location, UParticleSystem* FX)
{
	if (FX) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX, Location);
	}
}
