// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "Kismet/GameplayStatics.h"

float AHealthPotion::GetHealAmount()
{
	return HealAmount;
}

void AHealthPotion::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(Sound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}
