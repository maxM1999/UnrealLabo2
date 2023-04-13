// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"

#include <string>

#include "CharacterAttributes.h"
#include "HealthPotion.h"
#include "Pickable.h"

AAvatar::AAvatar()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsAlive = true;
	HealthPotionCount = 0;
}

void AAvatar::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(Attributes))
	{
		CurrentHealth = Attributes->MaxHealth;
	}
}

void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAvatar::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(!bIsAlive) return 0.0f;
	
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, GetMaxHealth());
	OnUpdateHealth();
	
	if(CurrentHealth == 0.f)
	{
		bIsAlive = false;
		OnDeath();		
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

float AAvatar::GetHealth() const
{
	return CurrentHealth;
}

float AAvatar::GetMaxHealth() const
{
	if(IsValid(Attributes))
	{
		return Attributes->MaxHealth;
	}
	return 0.f;
}

float AAvatar::GetPercentHealth() const
{
	if(GetHealth() > 0.f)
	{
		return GetHealth() / GetMaxHealth();	
	}
	return 0.f;
}

int32 AAvatar::GetHealthPotionCount() const
{
	return HealthPotionCount;
}

UTexture2D* AAvatar::GetPortrait() const
{
	if(IsValid(Attributes))
	{
		return Attributes->Portrait;
	}
	return nullptr;
}

bool AAvatar::IsAlive() const
{
	return bIsAlive;
}

void AAvatar::PickItem(APickable* Pickable)
{
	if(!IsValid(Pickable)) return;

	// Cela pourra être éventuellement des munitions
	AHealthPotion* HealthPotion = Cast<AHealthPotion>(Pickable);
	if(HealthPotion)
	{
		HealthPotionCount++;
		PossessedHealthPotions.Add(HealthPotion);
		FString PotionCountStr = FString::FromInt(HealthPotionCount);
		UpdateItemCount(PotionCountStr);
	}
}

void AAvatar::UseItem()
{
	if(HealthPotionCount == 0 || !IsValid(Attributes)) return;

	HealthPotionCount--;
	AHealthPotion* PotionToUse = PossessedHealthPotions.Pop();
	
	if(IsValid(PotionToUse))
	{
		// Redonner de la vie au personnage et mettre a jour la barre de vie.
		const float AmountToHeal = PotionToUse->GetHealAmount();
		CurrentHealth = FMath::Clamp(CurrentHealth + AmountToHeal, 0.f, Attributes->MaxHealth);
		OnUpdateHealth();

		// Mettre a jour le nombre de potions de vie dans le UI
		FString PotionCountStr = FString::FromInt(HealthPotionCount);
		UpdateItemCount(PotionCountStr);
		
		PotionToUse->Destroy();
	}
}








