// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "HealthPotion.h"


void UMyGameInstance::SetPotionCount(const int32& Count, const int32& HealAmount)
{
	PlayerHealthPotionCount = Count;
	HealthPotionHealAmount = HealAmount;
}

void UMyGameInstance::GetPotionCount(int32& OutCount, int32& OutHealAmount)
{
	OutCount = PlayerHealthPotionCount;
	OutHealAmount = HealthPotionHealAmount;
}

void UMyGameInstance::SetPlayerHealth(const int32& Health)
{
	PlayerHealth = Health;
}

int32 UMyGameInstance::GetPlayerHealth() const
{
	return PlayerHealth;
}
