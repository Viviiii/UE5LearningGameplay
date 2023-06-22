// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectFiles/Objects.h"
#include "Enemies/Enemy.h"
#include "EchoFiles/EchoCharacter.h"
#include "LoadLevel.generated.h"


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
		void respawn(AEnemy* newEnemy);

	FTimerHandle respawnTimer;
	
	FTimerDelegate respawnParam;

	int killNumber=0;
public :

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	AEnemy* newEnemy;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseCharacter> echoCharac;

	AEchoCharacter* echo;
	
};
