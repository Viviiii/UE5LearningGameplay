// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::PlayHitMontage(FName Section)
{
	UAnimInstance* montageHit = GetMesh()->GetAnimInstance();
	if (montageHit) {
		montageHit->Montage_Play(hitMontage);
		montageHit->Montage_JumpToSection(Section, hitMontage);
	}
}

void ABaseCharacter::PlayDeathMontage()
{
}

void ABaseCharacter::PlayAttackMontage()
{
}

void ABaseCharacter::attackEnd()
{
}

void ABaseCharacter::enableSwordCollision(ECollisionEnabled::Type CollisionEnabled)
{
}

void ABaseCharacter::disableSwordCollision(ECollisionEnabled::Type CollisionEnabled)
{
}

void ABaseCharacter::Attack()
{
}

void ABaseCharacter::PlayIdleMontage()
{
}

void ABaseCharacter::getHit_Implementation(const FVector& impactPoint)
{
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ABaseCharacter::DirectionalHit(const FVector& impactPoint)
{
}


