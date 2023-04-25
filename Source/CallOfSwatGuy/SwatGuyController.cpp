// Fill out your copyright notice in the Description page of Project Settings.


#include "SwatGuyController.h"
#include "Avatar.h"
#include "GameFramework/Character.h"
#include "SwatGuyAnimInstance.h"
#include "SwatGuyCharacter.h"
#include "MyGameInstance.h"
#include "PlayerInventory.h"
#include "HealthPotion.h"

ASwatGuyController::ASwatGuyController()
{
	ControlledCharacter = Cast<ASwatGuyCharacter>(GetPawn());

	bIsDancing = false;
}

void ASwatGuyController::BeginPlay()
{
	MouseCameraSensitivity *= 10;
	GamepadCameraSensitivity *= 10;

	// Initialiser ControlledPawn si l'assignation dans le constructeur n'a pas fonctionné
	if(!IsValid(ControlledCharacter))
	{
		ControlledCharacter = Cast<ASwatGuyCharacter>(GetPawn());
	}

	GameInstance = Cast<UMyGameInstance>(GetGameInstance());
}

void ASwatGuyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) return;

	InputComponent->BindAxis(TEXT("MoveForward"), this, &ASwatGuyController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ASwatGuyController::MoveRight);
	InputComponent->BindAxis(TEXT("LookVertical"), this, &ASwatGuyController::LookVertical);
	InputComponent->BindAxis(TEXT("LookHorizontal"), this, &ASwatGuyController::LookHorizontal);
	InputComponent->BindAxis(TEXT("GamepadLookVertical"), this, &ASwatGuyController::GamepadLookVertical);
	InputComponent->BindAxis(TEXT("GamepadLookHorizontal"), this, &ASwatGuyController::GamepadLookHorizontal);
	
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASwatGuyController::Crouch);
	InputComponent->BindAction(TEXT("Dance"), EInputEvent::IE_Pressed, this, &ASwatGuyController::Dance);
	InputComponent->BindAction(TEXT("UseItem"), EInputEvent::IE_Pressed, this, &ASwatGuyController::UseHealthPotion);
	InputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ASwatGuyController::Fire);
}

void ASwatGuyController::MoveForward(float InValue)
{
	if (InValue == 0.f) return;
	
	if (!IsValid(ControlledCharacter) || !ControlledCharacter->IsAlive()  || bIsDancing) return;

	const FVector ControlledAvatarForward = ControlledCharacter->GetActorForwardVector();
	ControlledCharacter->AddMovementInput(ControlledAvatarForward, InValue);
}

void ASwatGuyController::MoveRight(float InValue)
{
	if (InValue == 0.f) return;
	
	if (!IsValid(ControlledCharacter) || !ControlledCharacter->IsAlive()  || bIsDancing) return;

	const FVector ControlledAvatarRight = ControlledCharacter->GetActorRightVector();
	ControlledCharacter->AddMovementInput(ControlledAvatarRight, InValue);
}

void ASwatGuyController::LookVertical(float InValue)
{
	if (InValue == 0.f || !IsValid(GetWorld()) || !ControlledCharacter->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddPitchInput(InValue * MouseCameraSensitivity.Y * Dt);
}

void ASwatGuyController::LookHorizontal(float InValue)
{
	if (InValue == 0.f || !GetWorld() || !ControlledCharacter->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddYawInput(InValue * MouseCameraSensitivity.X * Dt);
}

void ASwatGuyController::GamepadLookVertical(float InValue)
{
	if (InValue == 0.f || !GetWorld() || !ControlledCharacter->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddPitchInput(InValue * GamepadCameraSensitivity.Y * Dt);
}

void ASwatGuyController::GamepadLookHorizontal(float InValue)
{
	if (InValue == 0.f || !IsValid(GetWorld()) || !ControlledCharacter->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddYawInput(InValue * GamepadCameraSensitivity.X * Dt);
}

void ASwatGuyController::Crouch()
{
	if (!IsValid(ControlledCharacter) || bIsDancing) return;

	if (!ControlledCharacter->bIsCrouched)
	{
		ControlledCharacter->Crouch();
	}
	else
	{
		ControlledCharacter->UnCrouch();
	}
}

void ASwatGuyController::Dance()
{
	bIsDancing = !bIsDancing;

	if(bIsDancing)
	{
		if(IsValid(ControlledCharacter))
		{
			ControlledCharacter->Dance();
		}
	}
	else
	{
		if(IsValid(ControlledCharacter))
		{
			ControlledCharacter->StopDancing();
		}
	}
	
	if (ACharacter* Char = Cast<ACharacter>(GetPawn()))
	{
		USwatGuyAnimInstance* AnimInstance = Cast<USwatGuyAnimInstance>(Char->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->ToggleIsDancing();
		}
	}
}

void ASwatGuyController::UseHealthPotion()
{
	UseItem(UHealthPotion::StaticClass());
}

void ASwatGuyController::UseItem(TSubclassOf<UBaseItem> ItemType)
{
	if (IsValid(GameInstance))
	{
		PlayerInventory* Inventory = GameInstance->GetPlayerInventory();
		if (Inventory && ControlledCharacter)
		{
			Inventory->UseItem(ItemType, ControlledCharacter);
			int32 NewItemCount = Inventory->GetItemCount(ItemType);
			const FString NewItemCountStr = FString::FromInt(NewItemCount);
			ControlledCharacter->UpdateItemCount(NewItemCountStr);
		}
	}
}

void ASwatGuyController::Fire()
{
	if(IsValid(ControlledCharacter))
	{
		ControlledCharacter->Fire();
	}
}
