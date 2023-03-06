// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable.h"
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

