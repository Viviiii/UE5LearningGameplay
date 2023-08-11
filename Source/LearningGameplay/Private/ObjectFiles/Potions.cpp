// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/Potions.h"
#include "Kismet/GameplayStatics.h"

void APotions::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (pickPotion) {
		UGameplayStatics::PlaySoundAtLocation(this, pickPotion, GetActorLocation());
	}
	if (OtherActor->ActorHasTag("EchoCharacter")) {
		IPickUpInterface* pickUpInterface = Cast<IPickUpInterface>(OtherActor);
		if (pickUpInterface && ActorHasTag("HealPotion")) {
			pickUpInterface->getHeal(this);
		}
		else {
			pickUpInterface->getStamina(this);
		}
		
	}
	Destroy();
	
}
