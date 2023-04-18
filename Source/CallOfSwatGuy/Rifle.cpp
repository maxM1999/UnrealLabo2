// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"



ARifle::ARifle() 
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RifleMesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(GetRootComponent());
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARifle::Equip(APawn* OwnerPawn, USceneComponent* ToAttach)
{
	if(!IsValid(ToAttach) || !IsValid(OwnerPawn)) return;
	
	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	AttachToComponent(ToAttach, Rules, EquippedSocket);

	SetOwner(OwnerPawn);
	SetInstigator(OwnerPawn);
}

void ARifle::UnEquipped(USceneComponent* ToAttach)
{
	if(!IsValid(ToAttach)) return;

	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	AttachToComponent(ToAttach, Rules, UnEquippedSocket);
}

void ARifle::SetSockets(const FName& InEquippedSocket,const FName& InUnEquippedSocket)
{
	EquippedSocket = InEquippedSocket;
	UnEquippedSocket = InUnEquippedSocket;
}

FTransform ARifle::GetMuzzleTransform() const
{
	if(IsValid(Muzzle))
	{
		return Muzzle->GetComponentTransform();
	}
	return FTransform::Identity;
}

