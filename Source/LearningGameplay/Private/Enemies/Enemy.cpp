// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "EchoFiles/CharacterStateEnum.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
//#include "BaseCharacter.cpp"

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
	StartHealth();
	AIenemy = Cast<AAIController>(GetController());
	Tags.Add(FName("Enemy"));
	if (pawnSensing) {
		pawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::pawnSeen);
	}

	SpawnDefaultWeapon();
	
	GetWorld()->GetTimerManager().SetTimer(patrolTimer, this, &AEnemy::patrolTimerFinished, 5.f, true);

}

void AEnemy::StartHealth()
{
	if (widgetHealth) {
		widgetHealth->SetVisibility(false);
		widgetHealth->setPercentHealth(1.f);
	}
}

void AEnemy::SpawnDefaultWeapon()
{
	if (weaponClass) {
		AWeapon* activeWeapon = GetWorld()->SpawnActor<AWeapon>(weaponClass, GetActorLocation(), GetActorRotation());
		activeWeapon->equip(GetMesh(), FName("WeaponSocket"), this, this);
		weaponEquipped = activeWeapon;
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
	/*else {
		CheckPatrolTarget();
	}*/
	

}

//void AEnemy::CheckPatrolTarget()
//{
//	//enemyState = EEnemyState::EES_Patrol;
//
//	if (targetPatrol) {
//		if (isTargetInRange(targetPatrol, patrolRadius)) {
//		}
//	}
//}


void AEnemy::getHit_Implementation(const FVector& impactPoint)
{
	ShowHealth();

	PlaySound(impactPoint);
	PlayVFX(impactPoint);
	if (IsAlive()) {
		DirectionalHit(impactPoint); 
	}
	else {
		EnemyDeath();
	}
}


bool AEnemy::IsAlive()
{
	return Attributes && Attributes->isAlive();
}

void AEnemy::ShowHealth()
{
	if (widgetHealth) {
		widgetHealth->SetVisibility(true);
	}
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::ReduceHealth(DamageAmount);
	if (widgetHealth) {
		widgetHealth->setPercentHealth(Attributes->getHealth());
	}
	return DamageAmount;
	combatTarget = EventInstigator->GetPawn();
	ChaseTarget();
	/*enemyState = EEnemyState::EES_Chasing;
	MoveToTarget(combatTarget);*/
	return DamageAmount;
}


void AEnemy::Destroyed()
{
	if (weaponEquipped) {
		weaponEquipped->Destroy();	
	}
}

void AEnemy::pawnSeen(APawn* pawn)
{
	bool shouldChaseTarget = !IsAttacking()
		&& !IsChasing()
		&& pawn->ActorHasTag(FName("EchoCharacter"));

	if (shouldChaseTarget) {
		GEngine->AddOnScreenDebugMessage(5, 1.5f, FColor::Blue, FString("I don't see you anymore"));
		combatTarget = pawn;
		ChaseTarget();
	}
	
}

void AEnemy::DirectionalHit(const FVector& impactPoint)
{
	const FVector forward = GetActorForwardVector();
	const FVector impactLow(impactPoint.X, impactPoint.Y, GetActorLocation().Z);
	const FVector hitPoint = (impactLow - GetActorLocation()).GetSafeNormal();

	const double Costheta = FVector::DotProduct(forward, hitPoint);
	double theta = FMath::Acos(Costheta);
	theta = FMath::RadiansToDegrees(theta);

	
	const FVector CrossP = FVector::CrossProduct(forward, hitPoint);

	if (CrossP.Z < 0) {
		theta *= -1.f;
	}
	
	FName Section("FromBack");

	if (theta <= 45.f && theta >= -45.f) {
		
		Section = FName("FrontHit");
	}
	else if (theta >= -100.f && theta <= -45.f) {
		
		Section = FName("LeftHit");
	}
	else if (theta <= 100.f && theta >= 45.f) {
		
		Section = FName("RightHit");
	}
	else if (theta >= 100.f || theta <= -100.f) {
		
		Section = FName("BackHit");
	}
	PlayHitMontage(Section);
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

/*IA attacks */
void AEnemy::enableSwordCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if (weaponEquipped && weaponEquipped->getBoxCollision()) {
		//GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Blue, FString::Printf(TEXT("Box name : %s"), weaponEquipped->getBoxCollision()->GetName()));
		//GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Blue, FString::Printf(FName(weaponEquipped->getBoxCollision()->GetName())));
		weaponEquipped->getBoxCollision()->SetCollisionEnabled(CollisionEnabled);
	}

}

void AEnemy::disableSwordCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if (weaponEquipped && weaponEquipped->getBoxCollision()) {
		weaponEquipped->getBoxCollision()->SetCollisionEnabled(CollisionEnabled);
		weaponEquipped->IgnoreActors.Empty();
	}
}

void AEnemy::attackEnd()
{
	enemyState = EEnemyState::EES_NoState;
	CheckCombatTarget();
}

/* IA state*/
bool AEnemy::IsAttacking()
{
	return enemyState == EEnemyState::EES_Attacking;
}

bool AEnemy::IsChasing()
{
	return enemyState == EEnemyState::EES_Chasing;
}

/* IA player distance*/
bool AEnemy::IsOutsideAttackRadius()
{
	return !isTargetInRange(combatTarget, attackRadius);
}

bool AEnemy::IsOutsideCombatRadius()
{
	return !isTargetInRange(combatTarget, combatRadius);
}

bool AEnemy::bCanAttack()
{
	return IsAlive() && !IsAttacking() && actionState == EActionState::EAS_Unoccupied;
}

/* IA Navigation */
void AEnemy::ChaseTarget()
{
	GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Blue, FString("Chasing"));
	GetWorld()->GetTimerManager().ClearTimer(attackTimer);
	actionState = EActionState::EAS_Unoccupied;
	enemyState = EEnemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	MoveToTarget(combatTarget);
}

void AEnemy::StartPatrolling()
{
	enemyState = EEnemyState::EES_Patrol;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	MoveToTarget(targetPatrol);
	GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::Blue, FString("Patrolling"));
}

void AEnemy::LoseInterest()
{
	GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::Blue, FString("LosingInterest"));
	GetWorld()->GetTimerManager().ClearTimer(attackTimer);
	combatTarget = nullptr;
	if (widgetHealth) {
		widgetHealth->SetVisibility(false);
	}
}

void AEnemy::CheckCombatTarget()	
{
	/*Ennemies lose interest, go back to patrolling*/
	if (IsOutsideCombatRadius()) {
		LoseInterest();
		StartPatrolling();
	}
	/* Enemies too far to attack so goes back to chasing*/
	else if (IsOutsideAttackRadius() && !IsChasing()) {
		ChaseTarget();
	}
	/* Enemies ATTAAAAAAAAAAAAACK*/
	else if (!IsOutsideAttackRadius() /*&& !IsAttacking()*/ && bCanAttack()) {
		/*enemyState =  EEnemyState::EES_Attacking;
		Attack();*/
		startAttackTimer();
	}
}

void AEnemy::Attack() {
	//Super::Attack();
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	actionState = EActionState::EAS_Attacking;
	PlayAttackMontage();

}

void AEnemy::startAttackTimer()
{
	enemyState = EEnemyState::EES_Attacking;
	GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Blue, FString("StartAttackTimer"));
	GetWorld()->GetTimerManager().SetTimer(attackTimer, this, &AEnemy::Attack, 1.5f, true, 0.2f);
}

bool AEnemy::isTargetInRange(AActor* target, double radius)
{
	const double distanceTarget = (target->GetActorLocation() - GetActorLocation()).Size();
	return (distanceTarget <= radius);
}

void AEnemy::MoveToTarget(AActor* target)
{
	if (target != nullptr) {
		FAIMoveRequest moveReq;
		moveReq.SetGoalActor(target);
		moveReq.SetAcceptanceRadius(10.f);
		FNavPathSharedPtr navPath;
		AIenemy->MoveTo(moveReq, &navPath);
	}
	if (target == nullptr) {
		return;
	}

}

void AEnemy::patrolTimerFinished()
{
	targetPatrol = choosingTarget();
	MoveToTarget(targetPatrol);
}

AActor* AEnemy::choosingTarget()
{
	TArray<AActor*> validActors;
	for (AActor* target : targetsPatrol) {
		if (target != targetPatrol) {
			validActors.AddUnique(target);
		}
	}
	if (validActors.Num() > 0) {
		const int32 selec = FMath::RandRange(0, validActors.Num() - 1);
		return validActors[selec];
	}
	return nullptr;
}

int32 AEnemy::PlayAttackMontage()
{
	return PlayRandomMontageSection(attackMontage, AttackMontageSections);
	/*UAnimInstance* montageAttack = GetMesh()->GetAnimInstance();
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
	}*/
}

/* Working differently*/
int32 AEnemy::PlayDeathMontage()
{
	//PlayRandomMontageSection(deathMontage, DeathMontageSections);
	const int32 selection = Super::PlayDeathMontage();
	TEnumAsByte<EDeathState> Pose(selection);
	deathPose = Pose;	
	return selection;
	/*UAnimInstance* montageDeath = GetMesh()->GetAnimInstance();
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
	}*/
}


void AEnemy::EnemyDeath()
{
	enemyState = EEnemyState::EES_Dead;
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetWorld()->GetTimerManager().ClearTimer(attackTimer);
	PlayDeathMontage();
	widgetHealth->DestroyComponent();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(3.f);
}