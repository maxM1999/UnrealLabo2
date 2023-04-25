// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class CALLOFSWATGUY_API UHealthPotion : public UBaseItem
{
	GENERATED_BODY()

public:
	UHealthPotion();
	virtual void Use(AActor* Owner) override;

private:
	float HealAmount;
	
	
};
