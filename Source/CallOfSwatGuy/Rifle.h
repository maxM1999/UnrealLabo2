// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

UCLASS()
class CALLOFSWATGUY_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	ARifle();
	virtual void Tick(float DeltaTime) override;

	/* Mettre l'arme dans les mains du personnage */
	void Equip(APawn* OwnerPawn, USceneComponent* ToAttach);

	/* Mettre l'arme dans le dos du personnage */
	void UnEquipped(USceneComponent* ToAttach);

	void SetSockets(const  FName& InEquippedSocket, const FName& InUnEquippedSocket);

	FTransform GetMuzzleTransform() const;

protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* Muzzle;

	FName EquippedSocket;
	FName UnEquippedSocket;
};
