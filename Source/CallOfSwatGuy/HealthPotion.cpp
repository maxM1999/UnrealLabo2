// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "SwatGuyCharacter.h"

UHealthPotion::UHealthPotion() : HealAmount(10.f)
{

}

void UHealthPotion::Use(AActor* Owner)
{
	if (AAvatar* Avatar = Cast<AAvatar>(Owner))
	{
		Avatar->Heal(HealAmount);
	}
}