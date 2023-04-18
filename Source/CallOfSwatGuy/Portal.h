// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UBoxComponent;

UCLASS()
class CALLOFSWATGUY_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void Move();

	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

	/* Time since the beginning */
	float Time;

	UPROPERTY(EditAnywhere)
	float MovementAmplitude;
	
	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	USoundBase* PortalSound;
};
