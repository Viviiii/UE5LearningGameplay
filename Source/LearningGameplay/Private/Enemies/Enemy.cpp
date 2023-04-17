// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "EchoFiles/CharacterStateEnum.h"
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

	Attributes = CreateDefaultSubobject<UEchoAttributes>(TEXT("EchoAttributes"));

	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	pawnSensing->bHearNoises = 812.f;
	pawnSensing->SightRadius = 877.f;
	pawnSensing->SetPeripheralVisionAngle(38.f);
	pawnSensing->LOSHearingThreshold = 1050.f;

	widgetHealth = CreateDefaultSubobject<UHealthBar>(TEXT("HealthBar"));
	widgetHealth->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;	
	bUseControllerRotationRoll = false;

	

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (widgetHealth) {
		widgetHealth->SetVisibility(false);
		widgetHealth->setPercentHealth(1.f);
	}
	AIenemy = Cast<AAIController>(GetController());
	if (pawnSensing) {
		//pawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::pawnSeen(APawn* pawn));
		pawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::pawnSeen);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*IA Attack*/
	if (enemyState > EEnemyState::EES_Patrol) {
		
		CheckCombatTarget();
	}
	else {
		
		/* IA Navigation*/
		//CheckPatrolTarget();
	}
	

}

void AEnemy::CheckPatrolTarget()
{
	enemyState = EEnemyState::EES_Patrol;
	if (isTargetInRange(targetPatrol, patrolRadius)) {
		
		targetPatrol = choosingTarget();
		GetWorld()->GetTimerManager().SetTimer(patrolTimer, this, &AEnemy::patrolTimerFinished, FMath::RandRange(1, 2) , true);
	}
}

void AEnemy::CheckCombatTarget()
{
	/*Ennemies lose interest, go back to patrolling*/
	
	if (!isTargetInRange(combatTarget, combatRadius)) {
		combatTarget = nullptr;
		if (widgetHealth) {
			widgetHealth->SetVisibility(false);
		}
		enemyState = EEnemyState::EES_Patrol;
		GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, FString("patrol"));
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		MoveToTarget(targetPatrol);

	}

	/* Enemies too far to attack so goes back to chasing*/
	else if (!isTargetInRange(combatTarget, combatRadius) && enemyState != EEnemyState::EES_Chasing) {
		enemyState = EEnemyState::EES_Chasing;
		GEngine->AddOnScreenDebugMessage(2, 0.5f, FColor::Red, FString("Chasing"));
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		MoveToTarget(combatTarget);
	}

	/* Enemies ATTAAAAAAAAAAAAACK*/
	else if (isTargetInRange(combatTarget, combatRadius) && enemyState != EEnemyState::EES_Attacking) {
		enemyState = EEnemyState::EES_Attacking;
		GEngine->AddOnScreenDebugMessage(3, 0.5f, FColor::Red, FString("Attacking"));
		//PlayAttackMontage();

	}
	
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

void AEnemy::PlayDeathMontage()
{
	UAnimInstance* montageDeath = GetMesh()->GetAnimInstance();
	if (montageDeath) {
		montageDeath->Montage_Play(deathMontage);
		int32 random = FMath::RandRange(0, 3);
		FName selection = FName();
		switch (random) {
			case 0:
				selection = FName("Death");
				deathState = EDeathState::ECS_Dead;
				break;

			case 1:
				selection = FName("DeathBis");
				deathState = EDeathState::ECS_Dead1;
				break;

			case 2:
				selection = FName("DeathForward");
				deathState = EDeathState::ECS_Dead2;
				break;

			case 3: 
				selection = FName("DeathLeft");
				deathState = EDeathState::ECS_Dead3;
				break;

			default:
				break;
		}
		montageDeath->Montage_JumpToSection(selection, deathMontage);
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

void AEnemy::PlayAttackMontage()
{
	UAnimInstance* montageAttack = GetMesh()->GetAnimInstance();
	if (montageAttack) {
		montageAttack->Montage_Play(attackMontage);
		int32 random = FMath::RandRange(0, 2);
		FName selection = FName();
		switch (random) {
		case 0:
			selection = FName("Attack");
			break;

		case 1:
			selection = FName("Attack1");
			break;

		case 2:
			selection = FName("Attack2");
			break;

		default:
			break;
		}
		montageAttack->Montage_JumpToSection(selection, attackMontage);
	}
}

bool AEnemy::isTargetInRange(AActor* target, double radius)
{
	const double distanceTarget = (target->GetActorLocation() - GetActorLocation()).Size();
	return (distanceTarget <= radius);
}

void AEnemy::MoveToTarget(AActor* target)
{
	//It's going here
	if (target == nullptr || AIenemy == nullptr) return ;

	FAIMoveRequest moveReq;
	moveReq.SetGoalActor(target);
	moveReq.SetAcceptanceRadius(10.f);
	FNavPathSharedPtr navPath;
	AIenemy->MoveTo(moveReq, &navPath);
	
}

void AEnemy::patrolTimerFinished()
{
	MoveToTarget(targetPatrol);
}

AActor* AEnemy::choosingTarget()
{
	//It's going here
	if (targetPatrol == nullptr || targetsPatrol.IsEmpty()) return nullptr;
	TArray<AActor*> validActors;
	for (AActor* target : targetsPatrol) {
		if (target != targetPatrol) {
			validActors.AddUnique(target);
		}
	}
	const int32 selec = FMath::RandRange(0, validActors.Num() - 1);
	return validActors[selec];

}


void AEnemy::getHit_Implementation(const FVector& impactPoint)
{
	if (widgetHealth) {
		widgetHealth->SetVisibility(true);
	}
	if (hitSound) {
		UGameplayStatics::PlaySoundAtLocation(this, hitSound, impactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bloodEffect, impactPoint);
		//widgetHealth->setPercentHealth(.8f);
	}
	if (Attributes && Attributes->isAlive()) {
		DirectionalHit(impactPoint);
	}

	else {
		PlayDeathMontage();
		widgetHealth->DestroyComponent();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetLifeSpan(3.f);
		
	}

	
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Attributes && widgetHealth) {
		Attributes->ReceiveDamage(DamageAmount);
		widgetHealth->setPercentHealth(Attributes->getHealth());
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Blue, FString::Printf(TEXT("HP : %f"),Attributes->getHealth()));
	}

	combatTarget = EventInstigator->GetPawn();
	enemyState = EEnemyState::EES_Chasing;
	MoveToTarget(combatTarget);
	return DamageAmount;
}

void AEnemy::pawnSeen(APawn* pawn)
{
	if (enemyState == EEnemyState::EES_Chasing) return;
	if (pawn->ActorHasTag(FName("EchoCharacter"))) {
		
		GetCharacterMovement()->MaxWalkSpeed = 450.f;
		combatTarget = pawn;
		GetWorld()->GetTimerManager().ClearTimer(patrolTimer);

		if (enemyState != EEnemyState::EES_Attacking) {
			enemyState = EEnemyState::EES_Chasing;
			MoveToTarget(combatTarget);
		}
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
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + forward * 50.f, 5.f, FColor::Red,15.f);
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + hitPoint * 50.f, 5.f, FColor::Blue, 15.f);
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

