// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundWave.h"
#include "IHitInterface.h"
#include "Treasure.h"
#include "Breakable.generated.h"



class UGeometryCollectionComponent;
class UCapsuleComponent;

UCLASS()
class LEARNINGGAMEPLAY_API ABreakable : public AActor, public IIHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void getHit_Implementation(const FVector& impactPoint);
private :

	UPROPERTY(VisibleAnywhere)
		class UGeometryCollectionComponent* breakable;

	UPROPERTY(EditAnywhere, Category = "Sound break")
		USoundBase* breakSound;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* capsule;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATreasure> treasureClass;

};
