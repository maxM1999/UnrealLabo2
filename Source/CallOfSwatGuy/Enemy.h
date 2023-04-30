// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AAvatar;

UCLASS()
class CALLOFSWATGUY_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnPerception(AActor* Other);

private:
	AAvatar* MyTarget = nullptr;

	UPROPERTY(EditAnywhere)
	float AttackRange = 200.f;

	/** BRAIN FUNCTIONS */
	bool IsDead();
	bool HasTarget();
	bool CanSeeTarget();
	bool CanAttackTarget();
	void AttackTarget();
	void ChaseTarget();
};
