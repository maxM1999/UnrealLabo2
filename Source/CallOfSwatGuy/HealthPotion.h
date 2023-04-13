// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickable.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class CALLOFSWATGUY_API AHealthPotion : public APickable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float HealAmount;

public:
	float GetHealAmount();
};
