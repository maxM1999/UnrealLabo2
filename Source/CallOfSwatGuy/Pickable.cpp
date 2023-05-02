// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable.h"
#include "SwatGuyCharacter.h"
#include "Components/SphereComponent.h"
#include "BaseItem.h"
#include "MyGameInstance.h"
#include "PlayerInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

APickable::APickable()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

void APickable::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(Sphere))
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickable::OnSphereBeginOverlap);
	}

	if (IsValid(Sound))
	{
		MyAudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, Sound, GetActorLocation());
	}
}

void APickable::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASwatGuyCharacter* Char = Cast<ASwatGuyCharacter>(OtherActor);
	if(IsValid(Char) && IsValid(ItemType))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if (IsValid(MyGameInstance))
		{
			PlayerInventory* Inventory = MyGameInstance->GetPlayerInventory();
			if (Inventory)
			{
				UBaseItem* NewItem = NewObject<UBaseItem>(GetWorld(), ItemType);
				if (IsValid(NewItem))
				{
					Inventory->AddItemToInventory(ItemType, NewItem);
					int32 CurrItemCount = Inventory->GetItemCount(ItemType);
					const FString ItemCountStr = FString::FromInt(CurrItemCount);
					Char->UpdateItemCount(ItemCountStr);
				}
			}
		}
	}

	DestroyPickable();
}

void APickable::DestroyPickable()
{
	if (IsValid(MyAudioComponent))
	{
		MyAudioComponent->Stop();
	}

	Destroy();
}

void APickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



