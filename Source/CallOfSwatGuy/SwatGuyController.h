// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SwatGuyController.generated.h"



class ASwatGuyCharacter;
class UBaseItem;

UCLASS()
class CALLOFSWATGUY_API ASwatGuyController : public APlayerController
{
	GENERATED_BODY()

public:
	ASwatGuyController();

private:
	ASwatGuyCharacter* ControlledCharacter;

	class UMyGameInstance* GameInstance;
	
	UPROPERTY(EditAnywhere, Category="Camera", meta=(ClampMin="0"), meta=(ClampMax="15"))
	FVector2D MouseCameraSensitivity;

	UPROPERTY(EditAnywhere, Category="Camera", meta = (ClampMin = "0"), meta = (ClampMax = "15"))
	FVector2D GamepadCameraSensitivity;

	bool bIsDancing;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void MoveForward(float InValue);
	void MoveRight(float InValue);
	void LookVertical(float InValue);
	void LookHorizontal(float InValue);
	void GamepadLookVertical(float InValue);
	void GamepadLookHorizontal(float InValue);
	void Crouch();
	void Dance();
	void UseHealthPotion();
	void UseItem(TSubclassOf<UBaseItem> ItemType);
	void Fire();

};
