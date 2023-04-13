// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAttributes.generated.h"

/**
 * 
 */
UCLASS()
class CALLOFSWATGUY_API UCharacterAttributes : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;
	
};
