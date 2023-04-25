// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class CALLOFSWATGUY_API PlayerInventory
{
public:
	PlayerInventory();
	~PlayerInventory();
	int32 GetItemCount(TSubclassOf<class UBaseItem> Type);
	void AddItemToInventory(TSubclassOf<UBaseItem> Type, UBaseItem* ItemToAdd);
	void UseItem(TSubclassOf<UBaseItem> Type, AActor* User);

private:
	TMap<TSubclassOf<UBaseItem>, TArray<UBaseItem*>> Inventory;
};
