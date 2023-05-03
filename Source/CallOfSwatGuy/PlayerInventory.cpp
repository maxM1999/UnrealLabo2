// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"
#include "BaseItem.h"
#include "HealthPotion.h"


PlayerInventory::PlayerInventory()
{
}

PlayerInventory::~PlayerInventory()
{
}

int32 PlayerInventory::GetItemCount(TSubclassOf<UBaseItem> Type)
{
	if (Inventory.Contains(Type))
	{
		return Inventory[Type].Num();
	}
	return 0;
}

void PlayerInventory::AddItemToInventory(TSubclassOf<UBaseItem> Type, UBaseItem* ItemToAdd)
{
	if (!IsValid(Type)) return;

	if (Inventory.Contains(Type))
	{
		TArray<UBaseItem*>* ItemArr = Inventory.Find(Type);
		if (ItemArr)
		{
			ItemArr->Add(ItemToAdd);
		}
	}
	else
	{
		TArray<UBaseItem*> NewItemArr;
		NewItemArr.Add(ItemToAdd);
		Inventory.Add(Type, NewItemArr);
	}

	const int32 FinalCnt = Inventory.Find(Type)->Num();
}

void PlayerInventory::UseItem(TSubclassOf<UBaseItem> Type, AActor* User)
{
	if (!IsValid(Type)) return;

	if (Inventory.Contains(Type))
	{
		TArray<UBaseItem*>* ItemArr = Inventory.Find(Type);
		if (ItemArr && ItemArr->Num() > 0)
		{
			UBaseItem* ItemPoped = ItemArr->Pop();
			if (IsValid(ItemPoped) && ItemPoped != nullptr)
			{
				ItemPoped->Use(User);

				// Retirer les item du root une fois utilisé.
				ItemPoped->RemoveFromRoot();
			}
		}
	}
}

void PlayerInventory::ClearItemsFromRoot()
{
	TArray<TSubclassOf<UBaseItem>> Keys;
	Inventory.GetKeys(Keys);

	for (TSubclassOf<UBaseItem> Key : Keys)
	{
		TArray<UBaseItem*> ItemArr = Inventory[Key];
		for (UBaseItem* Item : ItemArr)
		{
			Item->RemoveFromRoot();
		}
	}
}
