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
#include "Animation/AnimMontage.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

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

	//Attach between character and camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyesbrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyesbrows"));
	Eyesbrows->SetupAttachment(GetMesh());
	Eyesbrows->AttachmentName = FString("head");



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
	}

	Tags.Add(FName("EchoCharacter"));
	
}


// Called every frame
void AEchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AEchoCharacter::PlayAttackMontage()
{
	UAnimInstance* montageAttack = GetMesh()->GetAnimInstance();
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


	}
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
	if (characterState == ECharacterState::ECS_equippedWeapon && actionState == EActionState::EAS_Unoccupied) {
		PlayAttackMontage();
		actionState = EActionState::EAS_Attacking;
		
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

bool AEchoCharacter::canDraw() {

	return actionState == EActionState::EAS_Unoccupied && characterState == ECharacterState::ECS_Unequipped && weaponEquipped;

}

bool AEchoCharacter::canSheathe() {

	return actionState == EActionState::EAS_Unoccupied && characterState != ECharacterState::ECS_Unequipped && unarmMontage && weaponEquipped;
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

