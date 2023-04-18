// Fill out your copyright notice in the Description page of Project Settings.


#include "SwatGuyAnimInstance.h"

#include "Avatar.h"
#include "GameFramework/Character.h"

float USwatGuyAnimInstance::GetPawnSpeed() const
{
	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn)return 0.f;

	return Pawn->GetVelocity().Size();
}

float USwatGuyAnimInstance::GetPawnDirection() const
{
	APawn* Pawn = TryGetPawnOwner();
	if (!Pawn)return 0.f;

	const FVector PawnForward = Pawn->GetActorForwardVector();
	const FVector PawnDirection = Pawn->GetVelocity().GetSafeNormal();

	float AngleBetweenForwardAndDir = FMath::Acos(FVector::DotProduct(PawnForward, PawnDirection));
	AngleBetweenForwardAndDir = FMath::RadiansToDegrees(AngleBetweenForwardAndDir);

	const FVector PawnRight = Pawn->GetActorRightVector();
	float DotBetweenDirAndRight = FVector::DotProduct(PawnRight, PawnDirection);
	bool bAreTheSameDir = DotBetweenDirAndRight > 0;

	if (bAreTheSameDir)
	{
		return AngleBetweenForwardAndDir;
	}
	return -AngleBetweenForwardAndDir;
}

bool USwatGuyAnimInstance::IsPawnCrouched() const
{
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());

	if (!Character)return 0.f;

	return Character->bIsCrouched;
}

bool USwatGuyAnimInstance::IsAlive() const
{
	AAvatar* Avatar = Cast<AAvatar>(TryGetPawnOwner());
	if(IsValid(Avatar))
	{
		return Avatar->IsAlive();
	}
	return false;
}

float USwatGuyAnimInstance::GetControlPitch() const
{
	AAvatar* Avatar = Cast<AAvatar>(TryGetPawnOwner());
	if(IsValid(Avatar))
	{
		float Pitch = Avatar->GetControlRotation().Pitch;
		return FRotator::NormalizeAxis(Pitch);
	}

	return 0.f;
}

void USwatGuyAnimInstance::ToggleIsDancing()
{
	bIsDancing = !bIsDancing;
}
