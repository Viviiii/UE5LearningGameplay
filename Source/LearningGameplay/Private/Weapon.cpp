// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "WeaponStateEnum.h"
#include "EchoCharacter.h"

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

}

void AWeapon::equip(USceneComponent* weap, FName socketName)
{
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(weap, attachmentRules, socketName);
	weaponState = EWeaponState::EWS_Equipped;

}

void AWeapon::unEquip(USceneComponent* weap, FName socketName)
{
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(weap, attachmentRules, socketName);
}

void AWeapon::Sheathe(USceneComponent* weap, FName socketName)
{
}

/*
void AWeapon::Sheathe(USceneComponent* weap, FName socketName)
{
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(weap, attachmentRules, socketName);

}
*/

/* BROUILLOOOOOOON
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	echoCharacter = Cast<AEchoCharacter>(OtherActor);
	if (echoCharacter) {
		ItemMesh->AttachToComponent(echoCharacter->GetMesh(), attachmentRules, "WeaponSocket");
		amplitude = 0;
		speed = 0;
	}
	
*/
