// Fill out your copyright notice in the Description page of Project Settings.

#include "EchoCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GroomComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Objects.h"
#include "Weapon.h"
#include "Door.h"
#include "Animation/AnimMontage.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"

// Sets default values
AEchoCharacter::AEchoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	interact = false;

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
		overlappedWeapon->equip(GetMesh(), FName("WeaponSocket"));
		characterState = ECharacterState::ECS_equippedWeapon;
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
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, FString("Attacking!"));
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

void AEchoCharacter::PlayUnarmMontage()
{
	UAnimInstance* montageUnarm = GetMesh()->GetAnimInstance();
	if (montageUnarm) {
		montageUnarm->Montage_Play(unarmMontage);
		if (characterState == ECharacterState::ECS_Unequipped) {
			montageUnarm->Montage_JumpToSection("DrawSword", attackMontage);
			characterState = ECharacterState::ECS_equippedWeapon;
		}
		else {
			montageUnarm->Montage_JumpToSection("SheatheSword", attackMontage);
			characterState = ECharacterState::ECS_Unequipped;
		}
		


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

void AEchoCharacter::unarmedSword()
{
	characterState = ECharacterState::ECS_Unequipped;
}

void AEchoCharacter::UnarmWeapon()
{
	if (characterState != ECharacterState::ECS_Unequipped && actionState == EActionState::EAS_Unoccupied && unarmMontage) {
		PlayUnarmMontage();
	}

}

