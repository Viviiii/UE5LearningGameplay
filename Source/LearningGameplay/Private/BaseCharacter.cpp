// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	killNumber = 0;
}

void ABaseCharacter::PlayHitMontage(FName Section)
{
	UAnimInstance* montageHit = GetMesh()->GetAnimInstance();
	if (montageHit) {
		montageHit->Montage_Play(hitMontage);
		montageHit->Montage_JumpToSection(Section, hitMontage);
	}
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

FVector ABaseCharacter::GetTranslationWarpTarget()
{
	if (combatTarget == nullptr) return FVector();

	const FVector CombatTargetLocation = combatTarget->GetActorLocation();
	const FVector Location = GetActorLocation();
	FVector TargetToMe = (CombatTargetLocation - Location).GetSafeNormal();
	TargetToMe *= WarpTargetDistance;

	return CombatTargetLocation + TargetToMe;
}

FVector ABaseCharacter::GetRotationWarpTarget()
{
	if (combatTarget)
	{
		return combatTarget->GetActorLocation();
	}
	return FVector();
}

void ABaseCharacter::Attack()
{
}

void ABaseCharacter::PlayMontageSection(UAnimMontage* montage, const FName& section)
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && montage) {
		animInstance->Montage_Play(montage);
		animInstance->Montage_JumpToSection(section, montage);

	}
}

int32 ABaseCharacter::PlayRandomMontageSection(UAnimMontage* montage, TArray<FName> montageSections)
{
	if (montageSections.Num() <= 0) return 0;
	int32 random = FMath::RandRange(0, montageSections.Num() - 1);
	PlayMontageSection(montage, montageSections[random]);
	return random;
}

int32 ABaseCharacter::PlayDeathMontage()
{
	return PlayRandomMontageSection(deathMontage, DeathMontageSections);
}

int32 ABaseCharacter::PlayAttackMontage()
{
	return PlayRandomMontageSection(attackMontage, AttackMontageSections);
}

int32 ABaseCharacter::PlayIdleMontage()
{
	return PlayRandomMontageSection(idleMontage, IdleMontageSections);
}

void ABaseCharacter::StopAttackMontage()
{
	UAnimInstance* montageAttack = GetMesh()->GetAnimInstance();
	if (montageAttack) {
		montageAttack->Montage_Stop(0.25f, attackMontage);
	}
}

void ABaseCharacter::StopIdleMontage()
{
	UAnimInstance* montageIdle = GetMesh()->GetAnimInstance();
	if (montageIdle) {
		montageIdle->Montage_Stop(0.25f, idleMontage);
	}
}

bool ABaseCharacter::IsAlive()
{
	return Attributes && Attributes->isAlive();
}

void ABaseCharacter::setKillNumber()
{
	killNumber++;
}

void ABaseCharacter::PlayVFX(const FVector& impactPoint, UParticleSystem* FX)
{
	if (FX) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX, impactPoint);
	}
}

void ABaseCharacter::PlaySound(const FVector& impactPoint, USoundBase* sound)
{
	if (sound) {
		UGameplayStatics::PlaySoundAtLocation(this, sound, impactPoint);
	}
}

void ABaseCharacter::getHit_Implementation(const FVector& impactPoint, AActor* hitter)
{

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ABaseCharacter::DirectionalHit(const FVector& impactPoint)
{
}

void ABaseCharacter::ReduceHealth(float dmgAmount)
{
	if (Attributes) {
		Attributes->ReceiveDamage(dmgAmount);
	}
}


