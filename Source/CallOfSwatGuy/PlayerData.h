// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CALLOFSWATGUY_API PlayerData
{
public:
	PlayerData();
	~PlayerData();

	FORCEINLINE float GetHealth() const { return SavedHealth; }
	FORCEINLINE void SetHealth(float Health) { SavedHealth = Health; }

private:
	float SavedHealth = 0.f;
};
