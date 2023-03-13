// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/Weapon.h"
#include "ObjectFiles/WeaponStateEnum.h"
#include "Kismet/GameplayStatics.h"
#include "EchoFiles/EchoCharacter.h"
#include "Components/BoxComponent.h"
#include "IHitInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
	
}
void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector endTrace = BoxTraceEnd->GetComponentLocation();
	const FVector startTrace = BoxTraceStart->GetComponentLocation();
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult boxHit;

	for (AActor* Actors : IgnoreActors) {
		ActorsToIgnore.AddUnique(Actors);
	}


	UKismetSystemLibrary::BoxTraceSingle(this,
		startTrace,
		endTrace,
		FVector(5.5f, 5.5f, 5.5f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		boxHit,
		true);
	if (boxHit.GetActor()) {
		IIHitInterface* interfaceHit = Cast<IIHitInterface>(boxHit.GetActor());
		if (interfaceHit) {
			interfaceHit->getHit_Implementation(boxHit.ImpactPoint);
			
		}
		createField(boxHit.ImpactPoint);
		UGameplayStatics::ApplyDamage(boxHit.GetActor(), Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
		IgnoreActors.AddUnique(boxHit.GetActor());
	}


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

	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());

	VFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));
	VFX->SetupAttachment(GetRootComponent());

}

void AWeapon::equip(USceneComponent* weap, FName socketName, AActor* NewOwner, APawn* instigator)
{
	AttachMeshToComponent(weap, socketName);
	SetOwner(NewOwner);
	SetInstigator(instigator);
	weaponState = EWeaponState::EWS_Equipped;
	if (equipSound) {
		UGameplayStatics::PlaySoundAtLocation(this, equipSound, GetActorLocation());
	}
	if (VFX) {
		VFX->Deactivate();
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
