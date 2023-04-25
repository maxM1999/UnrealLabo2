// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class UCharacterAttributes;

UCLASS()
class CALLOFSWATGUY_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	AAvatar();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable)
	float GetPercentHealth() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetPortrait() const;

	UFUNCTION(BlueprintCallable)
	void FootstepsEvent();

	bool IsAlive() const;

	virtual void Heal(float Amount);



	/*******  PROPERTIES *******/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterAttributes* Attributes;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USoundBase* DirtSound;

	UPROPERTY(EditAnywhere)
	USoundBase* GrassSound;

	UPROPERTY(EditAnywhere)
	USoundBase* SandSound;

	float CurrentHealth;

private:
	bool PerformLineTrace(FHitResult& OutHit) const;
	void PlayFootstepsSoundFromHitSurface(UPhysicalMaterial* HitMaterial, const FVector& ImpactPoint);
	
	
	bool bIsAlive;
};
