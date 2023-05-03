// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class CALLOFSWATGUY_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AMeleeWeapon();
	void BeginSwing(AActor* Holder);
	void ResetSwing();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnWeaponHit(AActor* Other, AController* Controller);

private:
	TArray<AActor*> IgnoreActors;
	bool bIsSwinging = false;
	AActor* TheHolder;
};
