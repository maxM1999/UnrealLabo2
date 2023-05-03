// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"

AMeleeWeapon::AMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AMeleeWeapon::BeginSwing(AActor* Holder)
{
	TheHolder = Holder;
	IgnoreActors.Empty();
	IgnoreActors.AddUnique(Holder);
	bIsSwinging = true;
}

void AMeleeWeapon::ResetSwing()
{
	IgnoreActors.Empty();
	bIsSwinging = false;
}

void AMeleeWeapon::OnWeaponHit(AActor* Other, AController* Controller)
{
	if (bIsSwinging && !IgnoreActors.Contains(Other))
	{
		if (Controller)
		{
			UGameplayStatics::ApplyDamage(Other, 10.f, Controller, this, UDamageType::StaticClass());
			IgnoreActors.AddUnique(Other);
		}
	}
}

