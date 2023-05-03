// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Avatar.h"
#include "DrawDebugHelpers.h"
#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "MeleeWeapon.h"
#include "Engine/SkeletalMeshSocket.h"



AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (MeleeWeaponClass)
	{
		UWorld* World = GetWorld();
		MeleeWeapon = World->SpawnActor<AMeleeWeapon>(MeleeWeaponClass, FVector(), FRotator());

		const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
		if (IsValid(Socket))
		{
			Socket->AttachActor(MeleeWeapon, GetMesh());
		}
	}
	
}

void AEnemy::OnPerception(AActor* Other)
{
	if (IsValid(Other))
	{
		AAvatar* Target = Cast<AAvatar>(Other);
		if (IsValid(Target))
		{
			MyTarget = Target;
		}
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead())
	{
		if (HasTarget())
		{
			if (CanSeeTarget())
			{
				if (CanAttackTarget())
				{
					AAIController* AI = Cast<AAIController>(GetController());
					if (IsValid(AI))
					{
						AI->StopMovement();
					}
					AttackTarget(DeltaTime);
				}
				else
				{
					ChaseTarget();
				}
			}
		}
	}
}

void AEnemy::BeginAttack()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->BeginSwing(this);
	}
}

void AEnemy::EndAttack()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->ResetSwing();
	}
}

bool AEnemy::IsDead()
{
	// if health <= 0
	return false;
}

bool AEnemy::HasTarget()
{
	return MyTarget != nullptr;
}

bool AEnemy::CanSeeTarget()
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector Start = GetActorLocation();
	FVector End = MyTarget->GetActorLocation();
	UWorld* World = GetWorld();

	if (World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		DrawDebugLine(World, Start, End, FColor::Red);

		bool IsPlayer = Cast<AAvatar>(Hit.Actor) != nullptr;
		if (IsPlayer)
		{
			return true;
		}
	}

	return false;
}

bool AEnemy::CanAttackTarget()
{
	FVector Me = GetActorLocation();
	FVector Target = MyTarget->GetActorLocation();
	float Distance = FVector::Dist(Me, Target);
	if (Distance < AttackRange)
	{
		return true;
	}

	return false;
}

void AEnemy::AttackTarget(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("Attack"));

	AttackTimer -= DeltaTime;
	if (AttackTimer <= 0.f)
	{
		if (IsValid(AttackMontage))
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (IsValid(AnimInstance))
			{
				AnimInstance->Montage_JumpToSection(FName("Slash"), AttackMontage);
				AnimInstance->Montage_Play(AttackMontage);
			}
		}

		AttackTimer = AttackRate;
	}
}

void AEnemy::ChaseTarget()
{
	AAIController* AI = Cast<AAIController>(GetController());
	if (IsValid(AI))
	{
		AI->MoveToLocation(MyTarget->GetActorLocation());
	}
}
