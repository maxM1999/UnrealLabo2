// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class AHealthPotion;
class UCharacterAttributes;
class APickable;
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

	UFUNCTION(BlueprintPure, meta=(NotBlueprintThreadSafe="true"))
	int32 GetHealthPotionCount() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateHealth();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetPortrait() const;

	void PickItem(APickable* Pickable);

	UFUNCTION(BlueprintImplementableEvent, Category="MyEvents")
	void UpdateItemCount(const FString& NewPotionCount);

	bool IsAlive() const;

	void UseItem();


	/*******  PROPERTIES *******/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterAttributes* Attributes;

protected:
	virtual void BeginPlay() override;

private:
	float CurrentHealth;
	bool bIsAlive;
	int32 HealthPotionCount;
	TArray<AHealthPotion*> PossessedHealthPotions;
	
};
