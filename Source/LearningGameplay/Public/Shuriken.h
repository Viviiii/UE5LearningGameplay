// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shuriken.generated.h"

UCLASS()
class LEARNINGGAMEPLAY_API AShuriken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShuriken();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test variables")
		float speedBPW = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test variables")
		float speedBPO = 0.25f;

	float movCalcul(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	float runningTime;

	UPROPERTY(VisibleDefaultsOnly)
		float amplitude = 0.25f;

	UPROPERTY(VisibleDefaultsOnly)
		float speed = 0.25f;





};
