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
	if (OtherActor == echo) {
		SetActorLocation(changeLocation);
		/*respawnParam.BindUFunction(this, FName("respawn"), newEnemy);
		GetWorld()->GetTimerManager().SetTimer(respawnTimer, respawnParam, 10.f, true);*/
		GetWorld()->GetTimerManager().SetTimer(respawnTimer, this, &ALoadLevel::respawn, 10.f, true,0.1f);
	}
	
	
}

void ALoadLevel::respawnPaladins()
{
		//enemiesNumber = 0;
		FVector spawnLocation = FVector(
			FMath::RandRange(-18770, -13140),
			FMath::RandRange(-770, -6450),
			630);
		newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[0], spawnLocation, GetActorRotation());
		/*newEnemy->setEnemyNbr(1);
		enemiesNumber++;*/
		paladinsTab.Add(newEnemy);
		GEngine->AddOnScreenDebugMessage(4, 1.5f, FColor::Blue, FString::Printf(TEXT("Paladins number after: %d"), paladinsTab.Num()));

		/**/
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

	FVector spawnLocationR = FVector(
							-15054,
							-4239,
							910);

	//AEnemy* raptor;
	newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());
	if (newEnemy != nullptr) {
				if (newEnemy->spawnFX) {

					PlayVFX(spawnLocationR, newEnemy->spawnFX);
				}
			}

	newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());
	raptorsTab.Add(newEnemy);
	newEnemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());
	raptorsTab.Add(newEnemy);
	for (AEnemy* enemy : FGTab) {
		if (enemy->Attributes->getHealth() == 0) {
			GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Red, FString("Everyone is dead"));
		}
	}
	
}

void ALoadLevel::respawn()
{
		echo = Cast<AEchoCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		//AEnemy* enemy;
		GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::Blue, FString::Printf(TEXT("Paladins number before: %d"), paladinsTab.Num()));
		if (paladinsTab.Num() < 6) {
			respawnPaladins();
			
		}

		else if (echo->getKillNumber() == 5 && paladinsTab.Num() == 5) {

		}
	//	TArray<AActor*> FoundActors;

	//	if (/*enemy->getEnemyNbr() < 3 && echo->getKillNumber() <7*/enemiesNumber <6 && echo->getKillNumber() < 6) {
	//		enemiesNumber++;
	//		FVector spawnLocation = FVector(
	//			FMath::RandRange(-18770, -13140),
	//			FMath::RandRange(-770, -6450),
	//			630);
	//		GetWorld()->SpawnActor<AEnemy>(enemyClass[0], spawnLocation, GetActorRotation());
	//	}
	//	else if(echo->getKillNumber() == 5){

	//	GetWorld()->GetTimerManager().ClearTimer(respawnTimer);
	//	FVector spawnLocationFG = FVector(
	//		-16010,
	//		-4239,
	//		630);

	//	enemy = GetWorld()->SpawnActor<AEnemy>(enemyClass[1], spawnLocationFG, GetActorRotation());
	//	if (enemy->spawnFX) {
	//		PlayVFX(spawnLocationFG, enemy->spawnFX);
	//	}

	//	FVector spawnLocationR = FVector(
	//		-15054,
	//		-4239,
	//		910);

	//	AEnemy* raptor;
	//	raptor = GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());
	//	if (raptor != nullptr) {
	//		if (raptor->spawnFX) {

	//			PlayVFX(spawnLocationR, raptor->spawnFX);
	//		}
	//	}

	//	GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());
	//	GetWorld()->SpawnActor<AEnemy>(enemyClass[2], spawnLocationR, GetActorRotation());

	//}
}



void ALoadLevel::PlayVFX(FVector Location, UParticleSystem* FX)
{
	if (FX) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX, Location);
	}
}