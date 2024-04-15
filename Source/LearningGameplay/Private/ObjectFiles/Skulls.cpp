// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/Skulls.h"
#include "Kismet/GameplayStatics.h"


void ASkulls::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("EchoCharacter")) {
		IPickUpInterface* pickUpInterface = Cast<IPickUpInterface>(OtherActor);
		pickUpInterface->addKills(this);
			if (SFX) {
				UGameplayStatics::PlaySoundAtLocation(this, SFX, GetActorLocation());
			}
		
		Destroy();
	}
	
}
