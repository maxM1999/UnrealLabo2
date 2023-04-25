// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS()
class CALLOFSWATGUY_API UBaseItem : public UObject
{
	GENERATED_BODY()

public:
	UBaseItem();
	virtual void Use(AActor* Owner);
	
};
