// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Door.h"

#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(World, Location, 30.f, 24, FColor::Blue, false, 30.f);
// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemSubOject"));

	RootComponent = ItemMesh;


}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FVector LocForward = GetActorForwardVector();
	DRAW_SPHERE(Location);
	Location = Location + LocForward * 100.f;
	DRAW_SPHERE(Location);
	
	
	
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorWorldOffset -> allow to move the item every tick using DeltaTime
	//AddActorWorldRotation -> allow to rotate the item every tick using DeltaTime

}

