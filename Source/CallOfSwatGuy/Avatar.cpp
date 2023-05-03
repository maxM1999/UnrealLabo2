// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "CharacterAttributes.h"
#include "Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

AAvatar::AAvatar()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsAlive = true;
}

void AAvatar::BeginPlay()
{
	Super::BeginPlay();

	// Initialize avatar health
	if(IsValid(Attributes))
	{
		CurrentHealth = Attributes->MaxHealth;
	}
}

bool AAvatar::PerformLineTrace(FHitResult& OutHit) const
{
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActor(this);
	const FVector CurrLocation = GetActorLocation();
	const FVector LineTraceEnd = FVector(CurrLocation.X, CurrLocation.Y, CurrLocation.Z - 150.f);
	return GetWorld()->LineTraceSingleByChannel(OutHit, CurrLocation, LineTraceEnd, ECollisionChannel::ECC_Visibility, Params);
}

void AAvatar::PlayFootstepsSoundFromHitSurface(UPhysicalMaterial* HitMaterial, const FVector& ImpactPoint)
{
	switch(HitMaterial->SurfaceType)
	{
	case EPhysicalSurface::SurfaceType1: //Dirt
		if(IsValid(DirtSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, DirtSound, ImpactPoint);
		}
		break;
	case EPhysicalSurface::SurfaceType2: //Grass
		if(IsValid(GrassSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, GrassSound, ImpactPoint);
		}
		break;
	case EPhysicalSurface::SurfaceType3: //Sand
		if(IsValid(SandSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, SandSound, ImpactPoint);
		}
		break;
	default:
		break;
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

UTexture2D* AAvatar::GetPortrait() const
{
	if(IsValid(Attributes))
	{
		return Attributes->Portrait;
	}
	return nullptr;
}

void AAvatar::FootstepsEvent()
{
	FHitResult HitResult;
	bool bHit = PerformLineTrace(HitResult);
	if(bHit)
	{
		UPhysicalMaterial* PhysicalMaterial = HitResult.PhysMaterial.Get();
		if(IsValid(PhysicalMaterial))
		{
			const FVector ImpactPoint = HitResult.ImpactPoint;
			PlayFootstepsSoundFromHitSurface(PhysicalMaterial, ImpactPoint);
		}
	}
}

bool AAvatar::IsAlive() const
{
	return bIsAlive;
}

void AAvatar::Heal(float Amount)
{
	CurrentHealth += Amount;
	if (CurrentHealth > GetMaxHealth())
	{
		CurrentHealth = GetMaxHealth();
	}
}

