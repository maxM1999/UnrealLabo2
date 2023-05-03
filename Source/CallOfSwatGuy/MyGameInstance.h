// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class PlayerInventory;
class PlayerData;

UCLASS()
class CALLOFSWATGUY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	PlayerInventory* GetPlayerInventory() const;
	PlayerData* GetPlayerData() const;

private:
	PlayerInventory* Inventory;
	PlayerData* CharacterData;

};
