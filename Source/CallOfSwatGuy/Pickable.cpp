// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable.h"

#include "Avatar.h"
#include "Components/SphereComponent.h"

APickable::APickable()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

void APickable::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(Sphere))
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickable::OnSphereBeginOverlap);
	}
}

void APickable::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAvatar* Avatar = Cast<AAvatar>(OtherActor);
	if(IsValid(Avatar))
	{
		Avatar->PickItem(this);
		Deactivate();
	}
}

void APickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickable::Deactivate()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
}

