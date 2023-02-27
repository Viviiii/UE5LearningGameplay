// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "WeaponStateEnum.h"
#include "Kismet/GameplayStatics.h"
#include "EchoCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
	
}
void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Blue, FString("TOUUUUCH"));

	const FVector endTrace = BoxTraceEnd->GetComponentLocation();
	const FVector startTrace = BoxTraceStart->GetComponentLocation();
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult boxHit;

	UKismetSystemLibrary::BoxTraceSingle(this,
		startTrace,
		endTrace,
		FVector(5.5f, 5.5f, 5.5f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		boxHit,
		true);

}
void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

}

AWeapon::AWeapon()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());

	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::equip(USceneComponent* weap, FName socketName)
{
	AttachMeshToComponent(weap, socketName);
	weaponState = EWeaponState::EWS_Equipped;
	if (equipSound) {
		UGameplayStatics::PlaySoundAtLocation(this, equipSound, GetActorLocation());
	}

}

void AWeapon::AttachMeshToComponent(USceneComponent* weap, const FName& socketName)
{
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(weap, attachmentRules, socketName);
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
