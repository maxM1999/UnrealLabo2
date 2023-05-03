// Fill out your copyright notice in the Description page of Project Settings.


#include "SwatGuyCharacter.h"
#include "Rifle.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "PlayerInventory.h"
#include "HealthPotion.h"
#include "PlayerData.h"

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

void ASwatGuyCharacter::BeginPlay()
{
	Super::BeginPlay();

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

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance))
	{
		PlayerInventory* Inventory = GameInstance->GetPlayerInventory();
		if (Inventory)
		{
			int32 CurrPotionCnt = Inventory->GetItemCount(UHealthPotion::StaticClass());
			FString CurrItemCntStr = FString::FromInt(CurrPotionCnt);
			UpdateItemCount(CurrItemCntStr);
		}

		PlayerData* Data = GameInstance->GetPlayerData();
		if (Data)
		{
			float SavedHealth = Data->GetHealth();
			if (SavedHealth > 0 && SavedHealth <= GetMaxHealth())
			{
				CurrentHealth = SavedHealth;
				OnUpdateHealth();
			}
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

void ASwatGuyCharacter::Heal(float Amount)
{
	Super::Heal(Amount);

	OnUpdateHealth();
}
