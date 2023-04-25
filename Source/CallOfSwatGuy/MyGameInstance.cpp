// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerInventory.h"

void UMyGameInstance::Init()
{
	Super::Init();

	Inventory = new PlayerInventory();
}

PlayerInventory* UMyGameInstance::GetPlayerInventory() const
{
	return Inventory;
}



