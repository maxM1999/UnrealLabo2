// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class PlayerInventory;

UCLASS()
class CALLOFSWATGUY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init();
	PlayerInventory* GetPlayerInventory() const;

private:
	PlayerInventory* Inventory;

};
