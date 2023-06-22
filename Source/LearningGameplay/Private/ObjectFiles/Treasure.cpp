// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/Treasure.h"
#include "HUD/EchoInterface.h"
#include "Kismet/GameplayStatics.h"
#include <Components/WidgetComponent.h>
#include <HUD/EchoInterfaceComp.h>
#include <EchoFiles/EchoCharacter.h>

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (pickCoin) {
		UGameplayStatics::PlaySoundAtLocation(this, pickCoin, GetActorLocation());
	}
	IPickUpInterface* pickUpInterface = Cast<IPickUpInterface>(OtherActor);
	if (pickUpInterface) {
		pickUpInterface->addCoins(this);
	}
	Destroy();
}
