 // Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/Weapon.h"
#include "ObjectFiles/WeaponStateEnum.h"
#include "EchoFiles/CharacterStateEnum.h"
#include "Kismet/GameplayStatics.h"
#include "EchoFiles/EchoCharacter.h"
#include "Components/BoxComponent.h"
#include "Interfaces/IHitInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IgnoreActors.Empty();
	
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult boxHit;
	/* Echo hitted and the enemy or breakable is target, or enemy hitted and echo is target*/
	if (GetOwner()->ActorHasTag(TEXT("Enemy")) && OtherActor->ActorHasTag(TEXT("Enemy"))) return;

	BoxTraceWeapon(boxHit);
	if (boxHit.GetActor()) {
		if (GetOwner()->ActorHasTag(TEXT("Enemy")) && boxHit.GetActor()->ActorHasTag(TEXT("Enemy"))) return;

		/* Enemy hit the player*/
		if (GetOwner()->ActorHasTag("Enemy") && boxHit.GetActor()->ActorHasTag("EchoCharacter")) {
			UGameplayStatics::ApplyDamage(boxHit.GetActor(), Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
			ExecuteHit(boxHit.GetActor(), boxHit, GetOwner());
		}

		/* Player hit the enemy*/
		if (GetOwner()->ActorHasTag("EchoCharacter") && OtherActor->ActorHasTag("Enemy")) {
			
			UGameplayStatics::ApplyDamage(boxHit.GetActor(), Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
			ExecuteHit(boxHit.GetActor(), boxHit, GetOwner());
		}

		/*Player hit a breakable*/
		if (GetOwner()->ActorHasTag("EchoCharacter") && OtherActor->ActorHasTag("Breakable")) {

			ExecuteHit(OtherActor, boxHit, GetOwner());
			createField(boxHit.ImpactPoint);
		}
	}
}

/* if weapon hit Character, then function called*/
void AWeapon::ExecuteHit(AActor* OtherActor, FHitResult& boxHit, AActor* hitter)
{
	IIHitInterface* interfaceHit = Cast<IIHitInterface>(/*boxHit.GetActor()*/OtherActor);
	if (interfaceHit) {

		interfaceHit->getHit_Implementation(boxHit.ImpactPoint, GetOwner());

	}
}


void AWeapon::BoxTraceWeapon(FHitResult& boxHit)
{
	const FVector endTrace = BoxTraceEnd->GetComponentLocation();
	const FVector startTrace = BoxTraceStart->GetComponentLocation();
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
	
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	//GEngine->AddOnScreenDebugMessage(4, 3.f, FColor::Red, FString::Printf(TEXT("Size : %d"), ActorsToIgnore.Num()));

	/*It should only be working when the player is attacking*/
	UKismetSystemLibrary::BoxTraceSingle(this,
		startTrace,
		endTrace,
		FVector(15.5f, 15.5f, 15.5f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		boxHit,
		true);
	IgnoreActors.AddUnique(boxHit.GetActor());
	/*if (boxHit.GetActor()) {
		if (!boxHit.GetActor()->ActorHasTag("EchoCharacter")) {
			GEngine->AddOnScreenDebugMessage(4, 3.f, FColor::Red, FString(boxHit.GetActor()->GetName()));

			ActorsToIgnore.AddUnique(boxHit.GetActor());
		}
	}*/
	
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

	//Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
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

void AWeapon::dropWeapon(USceneComponent* weap)
{
	ItemMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	ItemMesh->DestroyComponent();
}

void AWeapon::unEquip(USceneComponent* weap, FName socketName)
{
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(weap, attachmentRules, socketName);
}

void AWeapon::setDmg(float multi)
{
	Damage *= multi;
}
