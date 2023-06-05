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
	
}

/* Not actually using the boxHit, to rework !*/
void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult boxHit;
	/* Echo hitted and the enemy or breakable is target, or enemy hitted and echo is target*/
	BoxTraceWeapon(boxHit);
	
	if (boxHit.GetActor()) {
		if (GetOwner()->ActorHasTag("Enemy") && boxHit.GetActor()->ActorHasTag("EchoCharacter")) {
			/*BoxTraceWeapon(boxHit);*/
			UGameplayStatics::ApplyDamage(boxHit.GetActor(), Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
			ExecuteHit(boxHit.GetActor(), boxHit, GetOwner());
		}
		if (GetOwner()->ActorHasTag("EchoCharacter") && OtherActor->ActorHasTag("Enemy")) {
			BoxTraceWeapon(boxHit);
			UGameplayStatics::ApplyDamage(boxHit.GetActor(), Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
			ExecuteHit(boxHit.GetActor(), boxHit, GetOwner());
		}
		if (GetOwner()->ActorHasTag("EchoCharacter") && OtherActor->ActorHasTag("Breakable")) {

			BoxTraceWeapon(boxHit);
			//UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
			ExecuteHit(OtherActor, boxHit, GetOwner());
			createField(boxHit.ImpactPoint);
		}
	}
	

	//if ((GetOwner()->ActorHasTag("EchoCharacter") && (OtherActor->ActorHasTag("Enemy") || OtherActor->ActorHasTag("Breakable")))
	//	|| (GetOwner()->ActorHasTag("Enemy") && OtherActor->ActorHasTag("EchoCharacter"))) {
	//	BoxTraceWeapon(boxHit);
	//	GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Red, FString(OtherActor->GetName()));
	//	/*if (boxHit.GetActor() != nullptr && (boxHit.GetActor()->ActorHasTag(FName("Breakable")) || boxHit.GetActor()->ActorHasTag(FName("Enemy")))) {*/
	//	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
	//	ExecuteHit(OtherActor, boxHit);
	//	createField(boxHit.ImpactPoint);
	//	IgnoreActors.AddUnique(boxHit.GetActor());
	//	//}	

	//}
	/*if (OtherActor->ActorHasTag("Enemy") || OtherActor->ActorHasTag("Breakable")) {
	
	}*/
	
}

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
	ActorsToIgnore.Add(GetOwner());


	/*for (AActor* Actors : IgnoreActors) {
		ActorsToIgnore.AddUnique(Actors);
	}*/
	/*It should only be working when the player is attacking*/
	UKismetSystemLibrary::BoxTraceSingle(this,
		startTrace,
		endTrace,
		FVector(5.5f, 5.5f, 5.5f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
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

void AWeapon::unEquip(USceneComponent* weap, FName socketName)
{
	const FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(weap, attachmentRules, socketName);
}
