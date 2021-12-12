// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PPBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

APPBasePickup::APPBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void APPBasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);
}

void APPBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if(GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

bool APPBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;	
}

void APPBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
	
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APPBasePickup::Respawn, RespawnTime);
}

void APPBasePickup::Respawn()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}

bool APPBasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}