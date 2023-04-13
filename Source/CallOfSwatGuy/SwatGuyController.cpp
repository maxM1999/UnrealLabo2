// Fill out your copyright notice in the Description page of Project Settings.


#include "SwatGuyController.h"

#include "Avatar.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "SwatGuyAnimInstance.h"

ASwatGuyController::ASwatGuyController()
{
	ControlledAvatar = Cast<AAvatar>(GetPawn());

	bIsDancing = false;
}

void ASwatGuyController::BeginPlay()
{
	MouseCameraSensitivity *= 10;
	GamepadCameraSensitivity *= 10;

	// Initialiser ControlledPawn si l'assignation dans le constructeur n'a pas fonctionné
	if(!IsValid(ControlledAvatar))
	{
		ControlledAvatar = Cast<AAvatar>(GetPawn());
	}
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
	InputComponent->BindAction(TEXT("UseItem"), EInputEvent::IE_Pressed, this, &ASwatGuyController::UseItem);
}

void ASwatGuyController::MoveForward(float InValue)
{
	if (InValue == 0.f) return;
	
	if (!IsValid(ControlledAvatar) || !ControlledAvatar->IsAlive()  || bIsDancing) return;

	const FVector ControlledAvatarForward = ControlledAvatar->GetActorForwardVector();
	ControlledAvatar->AddMovementInput(ControlledAvatarForward, InValue);
}

void ASwatGuyController::MoveRight(float InValue)
{
	if (InValue == 0.f) return;
	
	if (!IsValid(ControlledAvatar) || !ControlledAvatar->IsAlive()  || bIsDancing) return;

	const FVector ControlledAvatarRight = ControlledAvatar->GetActorRightVector();
	ControlledAvatar->AddMovementInput(ControlledAvatarRight, InValue);
}

void ASwatGuyController::LookVertical(float InValue)
{
	if (InValue == 0.f || !IsValid(GetWorld()) || !ControlledAvatar->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddPitchInput(InValue * MouseCameraSensitivity.Y * Dt);
}

void ASwatGuyController::LookHorizontal(float InValue)
{
	if (InValue == 0.f || !GetWorld() || !ControlledAvatar->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddYawInput(InValue * MouseCameraSensitivity.X * Dt);
}

void ASwatGuyController::GamepadLookVertical(float InValue)
{
	if (InValue == 0.f || !GetWorld() || !ControlledAvatar->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddPitchInput(InValue * GamepadCameraSensitivity.Y * Dt);
}

void ASwatGuyController::GamepadLookHorizontal(float InValue)
{
	if (InValue == 0.f || !IsValid(GetWorld()) || !ControlledAvatar->IsAlive() || bIsDancing) return;

	const float Dt = GetWorld()->GetDeltaSeconds();
	AddYawInput(InValue * GamepadCameraSensitivity.X * Dt);
}

void ASwatGuyController::Crouch()
{
	if (!IsValid(ControlledAvatar) || bIsDancing) return;

	if (!ControlledAvatar->bIsCrouched)
	{
		ControlledAvatar->Crouch();
	}
	else
	{
		ControlledAvatar->UnCrouch();
	}
}

void ASwatGuyController::Dance()
{
	bIsDancing = !bIsDancing;
	if (ACharacter* Char = Cast<ACharacter>(GetPawn()))
	{
		USwatGuyAnimInstance* AnimInstance = Cast<USwatGuyAnimInstance>(Char->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->ToggleIsDancing();
		}
	}
}

void ASwatGuyController::UseItem()
{
	if(IsValid(ControlledAvatar))
	{
		ControlledAvatar->UseItem();
	}
}
