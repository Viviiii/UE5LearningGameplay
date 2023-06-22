// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectFiles/Objects.h"
#include "EchoFiles/EchoCharacter.h"
#include "ObjectFiles/WeaponStateEnum.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/PickUpInterface.h"

// Sets default values
AObjects::AObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = ItemMesh;
	//ItemMesh->SetupAttachment(GetRootComponent());
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AObjects::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AObjects::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AObjects::OnSphereEndOverlap);
	
	
}

float AObjects::movCalcul(float value)
{
	return /*Amplitude :*/ amplitude * FMath::Sin(runningTime * /*Speed :*/ speed);
}
// Called every frame
void AObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	runningTime += DeltaTime;
	FVector Location = GetActorLocation();
	if (weaponState == EWeaponState::EWS_Pickable) {
		AddActorWorldOffset(FVector(0.f, 0.f, movCalcul(runningTime)));
		//AddActorWorldRotation(FRotator(0.f, 45.f * DeltaTime, 0.f));
	}
	
}

void AObjects::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickUpInterface* pickUpInterface = Cast<IPickUpInterface>(OtherActor);
	if (pickUpInterface) {
		pickUpInterface->setOverlappingItem(this);
	}
	/*AEchoCharacter* echoCharacter = Cast<AEchoCharacter>(OtherActor);
	if (echoCharacter) {
		echoCharacter->setOverlappingObject(this);
	}*/
}

void AObjects::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*AEchoCharacter* echoCharacter = Cast<AEchoCharacter>(OtherActor);
	if (echoCharacter) {
		echoCharacter->setOverlappingObject(nullptr);
	}*/
	IPickUpInterface* pickUpInterface = Cast<IPickUpInterface>(OtherActor);
	if (pickUpInterface) {
		pickUpInterface->setOverlappingItem(nullptr);
	}
}

