// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class AHealthPotion;

/**
 * 
 */
UCLASS()
class CALLOFSWATGUY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetPotionCount(const int32& Count, const int32& HealAmount);
	void GetPotionCount(int32& OutCount, int32& OutHealAmount);
	void SetPlayerHealth(const int32& Health);
	int32 GetPlayerHealth() const;

private:
	int32 PlayerHealthPotionCount;
	int32 HealthPotionHealAmount;
	int32 PlayerHealth = 0;
};
