// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/LoadLevel.h"
#include "Kismet/GameplayStatics.h"


void ALoadLevel::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Red, FString("Traveeeeeeeel"));
	UGameplayStatics::OpenLevel((UObject*)GetWorld(), FName("SnowMap"));*/
	/*FVector spawnLocation = FVector(-15750, -2520, 630);
	if (enemyNbr < 6) {
		newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass, spawnLocation, GetActorRotation());
		enemyNbr++;
	}*/
	//GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::Blue, FString::Printf(TEXT("Arena mode : %d"), newEnemy->arenaMode));
	/*  Move to random location */
	//newEnemy->MoveToRandomLocation();
	echo = Cast<AEchoCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	FVector changeLocation = FVector(
		FMath::RandRange(-18770, -13140),
		FMath::RandRange(-770, -6450),
		900);
	//if (OtherActor == echo) {
	//	SetActorLocation(changeLocation);
	//	respawnParam.BindUFunction(this, FName("respawn"), echo);
	//	GetWorld()->GetTimerManager().SetTimer(respawnTimer, respawnParam, 10.f, true, 0.1f);
	//	//GetWorld()->GetTimerManager().SetTimer(respawnTimer, this, &ALoadLevel::respawn, 10.f, true,0.1f);
	//}
	if (OtherActor == echo) {
		SetActorLocation(changeLocation);
		nextRound();
	}
	
	
}

//FTimerHandle ALoadLevel::respawnTimer(int paladinNumber, int echoKillNbr, float delay)
//{
//	FTimerHandle TimerHandle;
//	MyTimerManager->SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ALoadLevel::newPaladin, paladinNumber, echoKillNbr), delay, true);
//	return TimerHandle;
//}

//Respawn x paladins depending on the round
void ALoadLevel::respawnPaladins(int paladinNumber)
{
	GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::Blue, FString::Printf(TEXT("Paladins number : %d"), paladinNumber));
	GEngine->AddOnScreenDebugMessage(4, 1.5f, FColor::Blue, FString::Printf(TEXT("raptors number : %d"), raptorsNbr));

	//Spawn all paladins depending on round
	//respawnParam.BindUFunction(this, FName("newPaladin"), paladinNumber);
	//respawnParam.BindUFunction(this, FName("newPaladin"), echo->getKillNumber());
	respawnParam = FTimerDelegate::CreateUObject(this, &ALoadLevel::newPaladin, paladinNumber, echo->getKillNumber());
	//respawnTimer(paladinNumber, echo->getKillNumber(), FMath::RandRange(2.5f, 10.f));
	GetWorld()->GetTimerManager().SetTimer(respawnTimer, respawnParam, FMath::RandRange(2.5f, 10.f), true, 0.1f);
	//GetWorld()->GetTimerManager().SetTimer(respawnTimer, this, &ALoadLevel::newPaladin, FMath::RandRange(2.5f, 10.f), true, 0.1f);
}

void ALoadLevel::newPaladin(int paladinNumber, int echoKillNumber)
{
	//Add VFX ?
	
	FVector spawnLocation = FVector(
		FMath::RandRange(-18770, -13140),
		FMath::RandRange(-770, -6450),
		630);
	if (paladinsTab.Num() < paladinNumber) {
		newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[0], spawnLocation, GetActorRotation());
		paladinsTab.Add(newEnemy);

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
				-16010,
				-4239,
				630);

	newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[1], spawnLocationFG, GetActorRotation());
	FGTab.Add(newEnemy);
	if (newEnemy->spawnFX) {
		PlayVFX(spawnLocationFG, newEnemy->spawnFX);
	}
	respawnParam = FTimerDelegate::CreateUObject(this, &ALoadLevel::respawnRaptors, FGTab, raptorsNbr);
	//respawnParam.BindUFunction(this, FName("respawnRaptors"), FGTab);
	GetWorld()->GetTimerManager().SetTimer(respawnTimer, respawnParam, FMath::RandRange(6.5f, 10.f), true, 0.1f);

	//GetWorld()->GetTimerManager().SetTimer(respawnTimer, this, &ALoadLevel::respawnRaptors, FMath::RandRange(20.f, 45.f), true, 0.1f);
}

void ALoadLevel::respawnRaptors(TArray<AEnemy*> FireGiantArray, int raptors)
{
	if (FireGiantArray[0]->Attributes->getHealth() == 0) {	
		GetWorld()->GetTimerManager().ClearTimer(respawnTimer);
		FGTab.Empty();
		nextRound();
		
	}
	else {
		FVector spawnLocationR = FVector(
			-15054,
			-4239,
			910);
		for (int i = 0; i < raptors; i++) {
			newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());
		}
		
		if (newEnemy != nullptr) {
			if (newEnemy->spawnFX) {

				PlayVFX(spawnLocationR, newEnemy->spawnFX);
			}
		}
	}
}

void ALoadLevel::roundOne()
{
	//Call the respawn
	paladinsNbr = 1;
	raptorsNbr = 3;
	respawnPaladins(paladinsNbr);
	
}

void ALoadLevel::roundTwo()
{	
	paladinsNbr = 10;
	raptorsNbr = 4;
	respawnPaladins(paladinsNbr);
}

void ALoadLevel::nextRound()
{
	if (echo->Attributes->getKillFG() == 0) {
		roundOne();
	}
	else if (echo->Attributes->getKillFG() == 1) {
		roundTwo();
		//Second round
	}
}

void ALoadLevel::respawn(AEchoCharacter* echoCharac)
{
		
		//AEnemy* enemy;
		/*GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Blue, FString::Printf(TEXT("FG Time : %d"), echo->getKillNumber()));
		if (paladinsTab.Num() < 6) {
			respawnPaladins();
			
		}

		else if (echo->getKillNumber() == 6) {
			respawnFG();
		}*/
	
}

void ALoadLevel::PlayVFX(FVector Location, UParticleSystem* FX)
{
	if (FX) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX, Location);
	}
}