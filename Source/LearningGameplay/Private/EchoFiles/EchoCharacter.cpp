// Fill out your copyright notice in the Description page of Project Settings.

#include "EchoFiles/EchoCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GroomComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "ObjectFiles/Objects.h"
#include "ObjectFiles/Weapon.h"
#include "ObjectFiles/Door.h"
#include "HUD/EchoHUD.h"
#include "Animation/AnimMontage.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
//#include "BaseCharacter.cpp"

// Sets default values
AEchoCharacter::AEchoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetGenerateOverlapEvents(true);


	//Attach between character and camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 700.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyesbrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyesbrows"));
	Eyesbrows->SetupAttachment(GetMesh());
	Eyesbrows->AttachmentName = FString("head");

	Attributes = CreateDefaultSubobject<UEchoAttributes>(TEXT("EchoAttributes"));
	/*echoWidget = CreateDefaultSubobject<UEchoInterfaceComp>(TEXT("HealthBar"));
	echoWidget->SetupAttachment(GetRootComponent());*/



	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AEchoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		AEchoHUD* echoHUD = Cast<AEchoHUD>(PlayerController->GetHUD());
		if (echoHUD) {
			echoInterface = echoHUD->GetEchoInterface();
			if (echoInterface) {
				echoInterface->setPercentHealth(1.f);
				echoInterface->setPercentStamina(1.f);
				echoInterface->setKills();
			}
		}
	}


	/*if (musicGame) {
		UGameplayStatics::PlaySoundAtLocation(this, musicGame, GetActorLocation());
	}*/
	Tags.Add(FName("EchoCharacter"));
}

// Called every frame
void AEchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (actionState == EActionState::EAS_Unoccupied && Attributes->getStamina() < 1) {
		if (Attributes && echoInterface) {
			Attributes->setStamina(Attributes->getStamina() + 0.1);
			echoInterface->setPercentStamina(Attributes->getStamina() + 0.0001);
		}
	}

}

// Called to bind functionality to input
void AEchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Move);
		
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Look);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Interact);

		//Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Attack);
		
		//Sword Actions
		EnhancedInputComponent->BindAction(WeaponAction, ETriggerEvent::Triggered, this, &AEchoCharacter::UnarmWeapon);

		//Abilities Actions
		EnhancedInputComponent->BindAction(Ability1Action, ETriggerEvent::Triggered, this, &AEchoCharacter::Ability1);

		//Abilities Actions
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Dodge);

	}
}

void AEchoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (actionState == EActionState::EAS_Attacking) {
		return;
	}
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector DirectionF = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector DirectionR = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(DirectionF, MovementVector.Y);
		AddMovementInput(DirectionR, MovementVector.X);
	}
}

void AEchoCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEchoCharacter::Interact()
{
	AWeapon* overlappedWeapon = Cast<AWeapon>(overlappedObjects);
	if (overlappedWeapon) {

		overlappedWeapon->SetOwner(this);
		overlappedWeapon->SetInstigator(this);
		overlappedWeapon->equip(GetMesh(), FName("WeaponSocket"), this, this);
		characterState = ECharacterState::ECS_equippedWeapon;
		overlappedObjects = nullptr;
		weaponEquipped = overlappedWeapon;
	}

	ADoor* door = Cast<ADoor>(overlappedObjects);
	if (door) {
		door->doorOpening();
	}

}

void AEchoCharacter::Ability1()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && attackMontage) {
		animInstance->Montage_Play(attackMontage);
		animInstance->Montage_JumpToSection("Attack6", attackMontage);

	}
}

void AEchoCharacter::Dodge()
{
	if (actionState != EActionState::EAS_Unoccupied || Attributes->getStamina()<0.15) return;
		PlayDodgeMontage();
		actionState = EActionState::EAS_Dodge;
		if (Attributes && echoInterface) {
			Attributes->useStamina(15);
			echoInterface->setPercentStamina(Attributes->getStamina());
		}
}

void AEchoCharacter::PlayDodgeMontage()
{
	UAnimInstance* montageDodge = GetMesh()->GetAnimInstance();
	if (montageDodge && dodgeMontage) {
		montageDodge->Montage_Play(dodgeMontage);
		montageDodge->Montage_JumpToSection("Dodging", dodgeMontage);
	}
}

int32 AEchoCharacter::PlayAttackMontage()
{
	return PlayRandomMontageSection(attackMontage, AttackMontageSections);
	/*UAnimInstance* montageAttack = GetMesh()->GetAnimInstance();
	if (montageAttack) {
		montageAttack->Montage_Play(attackMontage);
		int32 random = FMath::RandRange(0, 1);
		FName selection = FName();
		switch (random) {
		case 0:
			selection = FName("Attack1");
			break;

		case 1:
			selection = FName("Attack2");
			break;

		default:
			break;
		}
		montageAttack->Montage_JumpToSection(selection, attackMontage);


	}*/
}

int32 AEchoCharacter::PlayIdleMontage()
{
	return PlayRandomMontageSection(idleMontage, IdleMontageSections);
}

void AEchoCharacter::PlayUnarmMontage(FName sectionName)
{
	UAnimInstance* montageUnarm = GetMesh()->GetAnimInstance();
	if (montageUnarm && unarmMontage) {
		montageUnarm->Montage_Play(unarmMontage);
		montageUnarm->Montage_JumpToSection(sectionName, unarmMontage);

	}
}
void AEchoCharacter::Attack()
{
	float actualStamina = Attributes->getStamina();
	if (characterState == ECharacterState::ECS_equippedWeapon && actionState == EActionState::EAS_Unoccupied && Attributes->getStamina() > 0.2) {
		PlayAttackMontage();
		actionState = EActionState::EAS_Attacking;
		if (Attributes) {
			Attributes->useStamina(20);
		}
		if (echoInterface) {
			echoInterface->setPercentStamina(Attributes->getStamina());
		}
		
	}
}

void AEchoCharacter::attackEnd()
{
	actionState = EActionState::EAS_Unoccupied;

}

void AEchoCharacter::disarmSword()
{
	if(weaponEquipped)
	weaponEquipped->AttachMeshToComponent(GetMesh(), FName("WeaponSheathedSocket"));
}

void AEchoCharacter::hitReactionEnd()
{
	actionState = EActionState::EAS_Unoccupied;
}

void AEchoCharacter::dodgeEnd()
{
	actionState = EActionState::EAS_Unoccupied;
}

void AEchoCharacter::StopDodgeMontage()
{
	UAnimInstance* montageDodge = GetMesh()->GetAnimInstance();
	if (montageDodge) {
		montageDodge->Montage_Stop(0.25f, dodgeMontage);
	}
}

void AEchoCharacter::enableSwordCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if (weaponEquipped && weaponEquipped->getBoxCollision()) {
		weaponEquipped->getBoxCollision()->SetCollisionEnabled(CollisionEnabled);
	}
	
}

void AEchoCharacter::disableSwordCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if (weaponEquipped && weaponEquipped->getBoxCollision()) {
	weaponEquipped->getBoxCollision()->SetCollisionEnabled(CollisionEnabled);
	weaponEquipped->IgnoreActors.Empty();
	}
}

float AEchoCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::ReduceHealth(DamageAmount);
	
	if (echoInterface) {
		echoInterface->setPercentHealth(Attributes->getHealth());
	}
	return DamageAmount;
}

void AEchoCharacter::setOverlappingItem(AObjects* item)
{
	overlappedObjects = item;
}

//void AEchoCharacter::addCoins(ATreasure* treasure)
//{
//	echoInterface->addCoins(treasure->coin);
//}

void AEchoCharacter::getHeal(APotions* potion)
{
	echoInterface->getHeal(Attributes->getHealth() + 25);
}

void AEchoCharacter::getStamina(APotions* potion)
{
	echoInterface->getStamina(Attributes->getStamina() + 25);
}

void AEchoCharacter::addKills(ASkulls* skull)
{
	echoInterface->addKills();
	killNumber++;

}

void AEchoCharacter::addFGKills(ASkulls* FG)
{
	echoInterface->addFGKills();
	Attributes->setKillFG();
	FGKillNumber++;
}

void AEchoCharacter::echoDeath()
{
	/*enemyState = EEnemyState::EES_Dead;
	GetCharacterMovement()->MaxWalkSpeed = 0.f;	
	PlayDeathMontage();
	widgetHealth->DestroyComponent();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(3.f);*/
}

bool AEchoCharacter::canDraw() {

	return actionState == EActionState::EAS_Unoccupied && characterState == ECharacterState::ECS_Unequipped && weaponEquipped;

}

bool AEchoCharacter::canSheathe() {

	return actionState == EActionState::EAS_Unoccupied && characterState != ECharacterState::ECS_Unequipped && unarmMontage && weaponEquipped;
}

int AEchoCharacter::getKillNumber()
{
	return killNumber;
}

void AEchoCharacter::setKillNumber()
{
	killNumber++;
}

void AEchoCharacter::getHit_Implementation(const FVector& impactPoint, AActor* hitter)
{
	PlaySound(impactPoint, hitSound);
	PlayVFX(impactPoint, bloodEffect);
	StopAttackMontage();
	StopDodgeMontage();	
	if (IsAlive() && hitter) {
		DirectionalHit(impactPoint);
		disableSwordCollision(ECollisionEnabled::NoCollision);
		actionState = EActionState::EAS_HitReaction;
		
	}
	if (hurtSound) {
		UGameplayStatics::PlaySoundAtLocation(this, hurtSound, GetActorLocation());
	}
}

void AEchoCharacter::DirectionalHit(const FVector& impactPoint)
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

void AEchoCharacter::UnarmWeapon()
{
	if (canSheathe()) {
		PlayUnarmMontage(FName("SheatheSword"));
		//weaponEquipped->AttachMeshToComponent(GetMesh(), FName("WeaponSheathedSocket"));
		characterState = ECharacterState::ECS_Unequipped;
			
	}
	else if (canDraw()) {
		PlayUnarmMontage(FName("DrawSword"));
		weaponEquipped->equip(GetMesh(), FName("WeaponSocket"), this, this);
		characterState = ECharacterState::ECS_equippedWeapon;
	}	
}

/*Inheritance test */
void AEchoCharacter::PlayHitMontage(FName Section)
{
	UAnimInstance* montageHit = GetMesh()->GetAnimInstance();
	if (montageHit) {
		montageHit->Montage_Play(hitMontage);
		montageHit->Montage_JumpToSection(Section, hitMontage);
	}
}

int32 AEchoCharacter::PlayDeathMontage()
{
	return PlayRandomMontageSection(deathMontage, DeathMontageSections);
}


/* Find super attack for the montage
* Find input for super attacks
* Create new attack state
* Create function to activate part of the montage
*/