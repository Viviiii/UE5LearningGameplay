// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "EchoCharacter.h"

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	echoCharacter = Cast<AEchoCharacter>(OtherActor);
	ItemMesh->AttachToComponent(echoCharacter->GetMesh(), attachmentRules, "WeaponSocket");
	amplitude = 0;
	speed = 0;
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
