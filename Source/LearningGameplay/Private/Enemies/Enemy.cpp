// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	PlayIdleMontage();
	
}



// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::PlayHitMontage(FName Section)
{
	UAnimInstance* montageHit = GetMesh()->GetAnimInstance();
	if (montageHit) {
		montageHit->Montage_Play(hitMontage);
		montageHit->Montage_JumpToSection(Section, hitMontage);
	}
}

void AEnemy::PlayIdleMontage()
{
	UAnimInstance* montageIdle = GetMesh()->GetAnimInstance();
	if (montageIdle) {
		montageIdle->Montage_Play(hitMontage);
		int32 random = FMath::RandRange(0, 3);
		FName selection = FName();
		switch (random) {
		case 0:
			selection = FName("IdleRoar");
			break;

		case 1:
			selection = FName("IdleFlexing");
			break;

		case 2:
			selection = FName("IdleChill");
			break;

		default:
			break;
		}
		montageIdle->Montage_JumpToSection(selection, idleMontage);
	}
}

void AEnemy::getHit_Implementation(const FVector& impactPoint)
{
	
	DirectionalHit(impactPoint);
	if (hitSound) {
		UGameplayStatics::PlaySoundAtLocation(this, hitSound, impactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bloodEffect, impactPoint);
	}
	
}

void AEnemy::DirectionalHit(const FVector& impactPoint)
{
	const FVector forward = GetActorForwardVector();
	const FVector impactLow(impactPoint.X, impactPoint.Y, GetActorLocation().Z);
	const FVector hitPoint = (impactLow - GetActorLocation()).GetSafeNormal();


	//DotProduct = forward * hitPoint = (|forward||hitPoint|) * cos(theta)
	//|forward||hitPoint| = 1 => DotProduct = forward * hitPoint = cos(theta)
	const double Costheta = FVector::DotProduct(forward, hitPoint);
	double theta = FMath::Acos(Costheta);
	theta = FMath::RadiansToDegrees(theta);

	//CrossProduct = forward x hitPoint = sin(theta)
	const FVector CrossP = FVector::CrossProduct(forward, hitPoint);

	if (CrossP.Z < 0) {
		theta *= -1.f;
	}
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + forward * 50.f, 5.f, FColor::Red,15.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + hitPoint * 50.f, 5.f, FColor::Blue, 15.f);
	FName Section("FromBack");

	if (theta <= 45.f && theta >= -45.f) {
		//GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, FString("FromFront"));
		Section = FName("FrontHit");
	}
	else if (theta >= -100.f && theta <= -45.f) {
		//GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, FString("FromLeft"));
		Section = FName("LeftHit");
	}
	else if (theta <= 100.f && theta >= 45.f) {
		//GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, FString("FromRight"));
		Section = FName("RightHit");
	}
	else if (theta >= 100.f || theta <= -100.f) {
		//GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, FString("FromBack"));
		Section = FName("BackHit");
	}
	//GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Blue, FString::Printf(TEXT("hitPoint X: %f"), impactPoint.X));
	//GEngine->AddOnScreenDebugMessage(2, 10.f, FColor::Blue, FString::Printf(TEXT("hitPoint Y: %f"), impactPoint.Y));
	PlayHitMontage(Section);
}

