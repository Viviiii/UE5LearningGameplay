// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class LEARNINGGAMEPLAY_API AObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float movCalcul(float value);

	UPROPERTY(EditAnywhere)
		float runningTime;

	UPROPERTY(VisibleDefaultsOnly)
		float amplitude = 0.25f;

	UPROPERTY(VisibleDefaultsOnly)
		float speed = 0.25f;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
		USphereComponent* Sphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) ;


};
