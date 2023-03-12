// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/Breakable.h"
#include "IHitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ABreakable::ABreakable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	breakable = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("BreakableActor"));
	SetRootComponent(breakable);
	breakable->SetGenerateOverlapEvents(true);
	breakable->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	breakable->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	capsule->SetupAttachment(GetRootComponent());
	capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

}

// Called when the game starts or when spawned
void ABreakable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakable::getHit_Implementation(const FVector& impactPoint)
{
	if (broken) return;	
	broken = true;
	if (treasureClasses.Num() > 0 && GetWorld()) {
		FVector Location = GetActorLocation();
		Location.Z += 70.f;
		int Selection = FMath::RandRange(0, treasureClasses.Num() - 1);
		GetWorld()->SpawnActor<ATreasure>(treasureClasses[Selection], Location, GetActorRotation());
		if (breakSound) {
			UGameplayStatics::PlaySoundAtLocation(this, breakSound, GetActorLocation());
		}
	}
	
}

