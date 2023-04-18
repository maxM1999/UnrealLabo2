// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SwatGuyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CALLOFSWATGUY_API USwatGuyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe = "true"))
	float GetPawnSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe = "true"))
	float GetPawnDirection() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe = "true"))
	bool IsPawnCrouched() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe = "true"))
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe = "true"))
	float GetControlPitch() const;

	void ToggleIsDancing();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	bool bIsDancing = false;
};
