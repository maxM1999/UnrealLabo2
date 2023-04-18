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

public:
	float GetHealAmount();
	
private:
	
	UPROPERTY(EditDefaultsOnly)
	float HealAmount;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* Sound;

protected:
	virtual void BeginPlay() override;
};
