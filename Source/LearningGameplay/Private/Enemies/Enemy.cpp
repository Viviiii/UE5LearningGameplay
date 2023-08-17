// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "EchoFiles/CharacterStateEnum.h"
#include "EchoFiles/EchoCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <HUD/EchoHUD.h>
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

AWeapon* AEnemy::getWeapon()
{
	if (weaponEquipped) {
		return weaponEquipped;
	}
	return nullptr;
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
	maxSpeed = GetCharacterMovement()->GetMaxSpeed();
	
	SpawnDefaultWeapon();
	echo = Cast<AEchoCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (targetPatrol && AIenemy) {	
		GetWorld()->GetTimerManager().SetTimer(patrolTimer, this, &AEnemy::patrolTimerFinished, FMath::RandRange(5.f, 10.5f), true);
	}
	else if(AIenemy){
		
		combatRadius = 5000.f;
		combatTarget = echo;
		ChaseTarget();
	}
	if (spawnMontage) {
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		PlaySpawnMontage();
	}
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
	if (enemyState > EEnemyState::EES_Patrol && AIenemy) {

		CheckCombatTarget();
	}

}

void AEnemy::getHit_Implementation(const FVector& impactPoint, AActor* hitter)	
{
	ShowHealth();
	//GetWorld()->GetTimerManager().ClearTimer(attackTimer);
	GetWorld()->GetTimerManager().ClearTimer(patrolTimer);
	StopAttackMontage();
	disableSwordCollision(ECollisionEnabled::NoCollision);
	PlaySound(impactPoint, hitSound);
	PlayVFX(impactPoint, bloodEffect);
	if (IsAlive()) {
		DirectionalHit(impactPoint); 
		if (hurtSound) {
			UGameplayStatics::PlaySoundAtLocation(this, hurtSound, GetActorLocation());
		}
	}
	else {
		
		EnemyDeath();
	}        
	
}


bool AEnemy::IsAlive()
{
	return Attributes && Attributes->isAlive();
}

int AEnemy::getEnemyNbr()
{
	return enemyNbr;
}

void AEnemy::setEnemyNbr(int value)
{
	enemyNbr = enemyNbr + value;
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
	combatTarget = EventInstigator->GetPawn();
	/*if(IsOutsideAttackRadius()){
		ChaseTarget();
	}*/
	if (enemyState != EEnemyState::EES_Attacking) {
		ChaseTarget();
	}
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

/*IA attacks */
void AEnemy::enableSwordCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if (weaponEquipped && weaponEquipped->getBoxCollision()) {
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
	
	GetWorld()->GetTimerManager().ClearTimer(attackTimer);
	actionState = EActionState::EAS_Unoccupied;
	enemyState = EEnemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = maxSpeed;
	GEngine->AddOnScreenDebugMessage(3,	 1.5f, FColor::Red, FString(combatTarget->GetName()));
	MoveToTarget(combatTarget);
}

void AEnemy::StartPatrolling()
{
	enemyState = EEnemyState::EES_Patrol;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	if (!targetPatrol) {
		MoveToRandomLocation();
	}
	else {
		
		MoveToTarget(targetPatrol);
	}

}

void AEnemy::LoseInterest()
{
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
		
		if (IsAttacking()) {
			StopAttackMontage();
		}
		ChaseTarget();
	}
	/* Enemies ATTAAAAAAAAAAAAACK*/
	else if (!IsOutsideAttackRadius() /*&& !IsAttacking()*/ && bCanAttack()) {
		/* If during attack, player too far, he misses, or stop attacking*/
		startAttackTimer();
	}
	
}

void AEnemy::Attack() {
	//Super::Attack();
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	actionState = EActionState::EAS_Attacking;
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2);
	PlayAttackMontage();

}

void AEnemy::destroyActor()
{
	Destroy();	
}

void AEnemy::startAttackTimer()
{

	enemyState = EEnemyState::EES_Attacking;
	GetWorld()->GetTimerManager().SetTimer(attackTimer, this, &AEnemy::Attack, FMath::RandRange(attackIntMin, attackIntMax), true, 0.2f);
}

bool AEnemy::isTargetInRange(AActor* target, double radius)
{
	if (target) {
		const double distanceTarget = (target->GetActorLocation() - GetActorLocation()).Size();
		return (distanceTarget <= radius);
	}
	else {
		return false;
	}
	
}

void AEnemy::MoveToTarget(AActor* target)
{
	if (target != nullptr) {
		
		FAIMoveRequest moveReq;
		
		moveReq.SetGoalActor(target);
		moveReq.SetAcceptanceRadius(10.f);
		FNavPathSharedPtr navPath;
		AIenemy->MoveTo(moveReq, &navPath);	
		GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Red, FString("Ouiii"));
			
	}
	if (target == nullptr) {
		GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Red, FString("NOOOOOOOOOOOOOOOOO"));
		return;
	}

}

void AEnemy::MoveToRandomLocation()
{
	//GetWorld()->GetTimerManager().ClearTimer(patrolTimer);

	FAIMoveRequest moveReq;

	FVector locationTarget = FVector(
		FMath::RandRange(-18770, -13140), 
		FMath::RandRange(-770, -6450),
		630);

	moveReq.SetGoalLocation(locationTarget);
	moveReq.SetAcceptanceRadius(10.f);
	FNavPathSharedPtr navPath;
	AIenemy->MoveTo(moveReq, &navPath);

	
}

void AEnemy::patrolTimerFinished()
{
	PlayIdleMontage();
	targetPatrol = choosingTarget();
	StopIdleMontage();
	
	if (!targetPatrol) {
		MoveToRandomLocation();
	}
	else {
		
		MoveToTarget(targetPatrol);
	}
	
}

//void AEnemy::respawnEnemyTimer()
//{
//	GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Red, FString("Respaaaawn"));
//	FVector spawnLocation = FVector(-530, -860, 110);
//	GetWorld()->SpawnActor<AEnemy>(enemyClass, spawnLocation, GetActorRotation());
//}

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
	
}

/* Working differently*/
int32 AEnemy::PlayDeathMontage()
{
	const int32 selection = Super::PlayDeathMontage();
	TEnumAsByte<EDeathState> Pose(selection);
	deathPose = Pose;	
	return selection;
}

void AEnemy::PlaySpawnMontage()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance) {
		animInstance->Montage_Play(spawnMontage);
		animInstance->Montage_JumpToSection(FName("Spawn"), spawnMontage);

	}
}

int32 AEnemy::PlayIdleMontage()
{
	
	const int32 selection = Super::PlayIdleMontage();
	TEnumAsByte<EEnemyIdleState> Pose(selection);
	idlePose = Pose;
	return selection;
}


void AEnemy::EnemyDeath()
{
	enemyState = EEnemyState::EES_Dead;
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetWorld()->GetTimerManager().ClearTimer(attackTimer);
	PlayDeathMontage();
	widgetHealth->DestroyComponent();
	disableSwordCollision(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (!targetPatrol) {
		//setEnemyNbr(-1);
		GetWorld()->SpawnActor<AObjects>(skullClass, GetActorLocation(), GetActorRotation());
	}
}