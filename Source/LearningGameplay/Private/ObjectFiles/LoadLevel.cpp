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
}

void ALoadLevel::respawn(AEnemy* enemy)
{
	echo = Cast<AEchoCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (enemy->getEnemyNbr() < 3 && echo->getKillNumber() <2) {

		FVector spawnLocation = FVector(
			FMath::RandRange(-18770, -13140),
			FMath::RandRange(-770, -6450),
			630);
		GetWorld()->SpawnActor<AEnemy>(enemyClass[0], spawnLocation, GetActorRotation());
		enemy->setEnemyNbr(1);
		//killNumber++;	
	}
	GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Blue, FString::Printf(TEXT("Nombre kills : %d"), echo->getKillNumber()));
	if (/*enemy->getEnemyNbr() ==0 && */echo->getKillNumber() >2) {
		GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::Red, FString("Here we are "));
		FVector spawnLocation = FVector(
			FMath::RandRange(-18770, -13140),
			FMath::RandRange(-770, -6450),
			630);
		GetWorld()->SpawnActor<AEnemy>(enemyClass[1], spawnLocation, GetActorRotation());
		enemy->setEnemyNbr(1);
		//killNumber++;
		GetWorld()->GetTimerManager().ClearTimer(respawnTimer);
	}
	
}

void ALoadLevel::BeginPlay()
{
	
	FVector spawnLocation = FVector(
		FMath::RandRange(-18770, -13140),
		FMath::RandRange(-770, -6450),
		630);
	newEnemy =  GetWorld()->SpawnActor<AEnemy>(enemyClass[0], spawnLocation, GetActorRotation());
	newEnemy->setEnemyNbr(1);
	//killNumber++;
	respawnParam.BindUFunction(this, FName("respawn"), newEnemy);
	GetWorld()->GetTimerManager().SetTimer(respawnTimer, respawnParam, 5.f, true);
}

void ALoadLevel::Tick(float DeltaTime)
{
	/*FVector spawnLocation = FVector(-15750, -2520, 630);
	GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Blue, FString::Printf(TEXT("Deltatime : %d"),DeltaTime));
	if (DeltaTime < 1) {
		newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass, spawnLocation, GetActorRotation());
	}*/
}