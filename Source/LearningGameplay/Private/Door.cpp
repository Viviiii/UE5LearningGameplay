// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	amplitude = 0;
	speed = 0;

}

void ADoor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


}

void ADoor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString("La porte se ferme "));
	if (open) {
		AddActorWorldRotation(FRotator(0.f, -90.0, 0.f));
		open = false;
	}
	
	
}

void ADoor::doorOpening()
{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Blue, FString("La porte s'ouvre"));
		AddActorWorldRotation(FRotator(0.f, -90.0, 0.f));
		open = true;
}


