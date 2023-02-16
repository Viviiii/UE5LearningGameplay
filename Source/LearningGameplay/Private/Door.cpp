// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "EchoCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(World, Location, 30.f, 24, FColor::Blue, false, 30.f);
// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());


}

// Called when the gam	e starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	open = false;
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnSphereEndOverlap);
	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FVector LocForward = GetActorForwardVector();
	DRAW_SPHERE(Location);
	Location = Location + LocForward * 100.f;
	DRAW_SPHERE(Location);
	
	
	
	
}

void ADoor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator rotationCom = ItemMesh->GetComponentRotation();

	//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, FString::Printf(TEXT("Rotation: %f"), rotationCom.Yaw));
	if (!open) {
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, FString("La porte s'ouvre"));
		
		AddActorWorldRotation(FRotator(0.f, -90.0, 0.f));
		open = true;
	}
	/*
	if (rotationCom.Roll == -180.f) {
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, FString("Porte fermée AHAHA"));
		AddActorWorldRotation(FRotator(0.f, 0.f, -90.f));
	}*/
	
}

void ADoor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (open) {
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, FString("La porte se ferme"));
		AddActorWorldRotation(FRotator(0.f, +90.0, 0.f));
		open = false;
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorWorldOffset -> allow to move the item every tick using DeltaTime
	//AddActorWorldRotation -> allow to rotate the item every tick using DeltaTime

}

