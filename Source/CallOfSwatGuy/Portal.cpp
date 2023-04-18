// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

#include "SwatGuyCharacter.h"
#include "MyGameInstance.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &APortal::APortal::OnBoxBeginOverlap);

	if(IsValid(PortalSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, PortalSound, GetActorLocation());
	}
}

void APortal::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASwatGuyCharacter* Char = Cast<ASwatGuyCharacter>(OtherActor);
	if(IsValid(Char))
	{
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if(IsValid(GameInstance))
		{
			GameInstance->SetPotionCount(Char->GetHealthPotionCount(), Char->GetHealthPotionHealAmount());
			GameInstance->SetPlayerHealth(Char->GetHealth());
		}
		UGameplayStatics::OpenLevel(this, FName("OtherDimension"));
	}
}

void APortal::Move()
{
	float ZOffset = MovementAmplitude * FMath::Sin(Time * MovementSpeed);
	FVector CurrLoc = GetActorLocation();
	FVector NewLoc = FVector(CurrLoc.X, CurrLoc.Y, CurrLoc.Z + ZOffset);
	SetActorLocation(NewLoc);
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;
	Move();
}

