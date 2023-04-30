// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Avatar.h"
#include "DrawDebugHelpers.h"
#include "AIController.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
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
					AttackTarget();
				}
				else
				{
					ChaseTarget();
				}
			}
		}
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

void AEnemy::AttackTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString("Attack"));
}

void AEnemy::ChaseTarget()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString("Chase"));

	AAIController* AI = Cast<AAIController>(GetController());
	if (IsValid(AI))
	{
		AI->MoveToLocation(MyTarget->GetActorLocation());
	}
}
