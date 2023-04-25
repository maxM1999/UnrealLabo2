// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar.h"
#include "SwatGuyCharacter.generated.h"

/**
 * 
 */

class ARifle;
class APickable;

UCLASS()
class CALLOFSWATGUY_API ASwatGuyCharacter : public AAvatar
{
	GENERATED_BODY()

public:
	ASwatGuyCharacter();

	void Dance();
	void StopDancing();
	void Fire();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaSeconds) override;

	/* Update health bar widget */
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateHealth();

	/* Update item count widget */
	UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
	void UpdateItemCount(const FString& NewPotionCount);

	virtual void Heal(float Amount) override;

protected:
	virtual void BeginPlay() override;

private:
	void SpawnMuzzleFlash();
	void PlayMontage(UAnimMontage* ToPlay, const FName& Section);
	void PlayFireSound();

	
	ARifle* Rifle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARifle> RifleClass;

	UPROPERTY(EditAnywhere)
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* FireSound;
	
};
