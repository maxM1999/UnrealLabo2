// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerInventory.h"
#include "PlayerData.h"

void UMyGameInstance::Init()
{
	Super::Init();

	Inventory = new PlayerInventory();
	CharacterData = new PlayerData();
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	// Enlever les item restant de l'inventaire du root
	Inventory->ClearItemsFromRoot();
}

PlayerInventory* UMyGameInstance::GetPlayerInventory() const
{
	return Inventory;
}

PlayerData* UMyGameInstance::GetPlayerData() const
{
	return CharacterData;
}



