// Fill out your copyright notice in the Description page of Project Settings.


#include "SwatGuyCharacter.h"
#include "Rifle.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterAttributes.h"
#include "HealthPotion.h"
#include "MyGameInstance.h"

ASwatGuyCharacter::ASwatGuyCharacter() : Rifle(nullptr)
{
}

void ASwatGuyCharacter::Dance()
{
	if(IsValid(Rifle))
	{
		Rifle->UnEquipped(GetMesh());
	}
}

void ASwatGuyCharacter::StopDancing()
{
	if(IsValid(Rifle))
	{
		Rifle->Equip(this, GetMesh());
	}
}

void ASwatGuyCharacter::Fire()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(!IsValid(AnimInstance) || !IsValid(FireMontage)) return;

	PlayMontage(FireMontage, FName("FireLoop"));
	SpawnMuzzleFlash();
	PlayFireSound();
}

void ASwatGuyCharacter::UseItem()
{
	if (HealthPotionCount == 0 || !IsValid(Attributes)) return;

	HealthPotionCount--;

	// Redonner de la vie au personnage et mettre a jour la barre de vie.
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthPotionHealAmount, 0.f, Attributes->MaxHealth);
	OnUpdateHealth();

	// Mettre a jour le nombre de potions de vie dans le UI
	FString PotionCountStr = FString::FromInt(HealthPotionCount);
	UpdateItemCount(PotionCountStr);
}

float ASwatGuyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ReturnedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnUpdateHealth();
	return ReturnedDamage;
}

void ASwatGuyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASwatGuyCharacter::PickItem(APickable* Pickable)
{
	if (!IsValid(Pickable)) return;

	// Cela pourra être éventuellement des munitions
	AHealthPotion* HealthPotion = Cast<AHealthPotion>(Pickable);
	if (HealthPotion)
	{
		HealthPotionCount++;
		HealthPotionHealAmount = HealthPotion->GetHealAmount();
		FString PotionCountStr = FString::FromInt(HealthPotionCount);
		UpdateItemCount(PotionCountStr);
	}
}

int32 ASwatGuyCharacter::GetHealthPotionCount() const
{
	return HealthPotionCount;
}

int32 ASwatGuyCharacter::GetHealthPotionHealAmount() const
{
	return HealthPotionHealAmount;
}

void ASwatGuyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if(IsValid(GameInstance))
	{
		GameInstance->GetPotionCount(HealthPotionCount, HealthPotionHealAmount);
		const FString ItemCountStr = FString::FromInt(HealthPotionCount);
		UpdateItemCount(ItemCountStr);

		CurrentHealth = GameInstance->GetPlayerHealth();
		if(CurrentHealth == 0 || CurrentHealth > GetMaxHealth())
		{
			CurrentHealth = GetMaxHealth();
		}
		OnUpdateHealth();
	}

	// Equip the rifle
	if(IsValid(RifleClass))
	{
		Rifle = GetWorld()->SpawnActor<ARifle>(RifleClass);
		
		if(IsValid(Rifle))
		{
			Rifle->SetSockets(FName("Gun_Socket"), FName("Back_Socket"));
			Rifle->Equip(this, GetMesh());
		}
	}
}

void ASwatGuyCharacter::SpawnMuzzleFlash()
{
	if(IsValid(Rifle) && IsValid(MuzzleFlash))
	{
		const FTransform MuzzleTransform = Rifle->GetMuzzleTransform();
		const FRotator MuzzleRot = MuzzleTransform.GetRotation().Rotator();
		UGameplayStatics::SpawnEmitterAtLocation(this, MuzzleFlash, MuzzleTransform.GetLocation(), Rifle->GetActorRotation());
	}
}

void ASwatGuyCharacter::PlayMontage(UAnimMontage* ToPlay, const FName& Section)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(!IsValid(AnimInstance) || !IsValid(ToPlay)) return;

	AnimInstance->Montage_Play(ToPlay);
	AnimInstance->Montage_JumpToSection(Section);
}

void ASwatGuyCharacter::PlayFireSound()
{
	if(IsValid(FireSound) && IsValid(Rifle))
	{
		const FVector MuzzleLocation = Rifle->GetMuzzleTransform().GetLocation();
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, MuzzleLocation);
	}
}
