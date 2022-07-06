// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_BoatBase.h"

// Sets default values
ACpp_BoatBase::ACpp_BoatBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BuoyancyComponent = CreateDefaultSubobject<UBuoyancyComponent>("Buoyancy");
}

// Called when the game starts or when spawned
void ACpp_BoatBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACpp_BoatBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Keeps buoyancy enabled so it does not sink when floating through different bodies of water.
	BuoyancyComponent->EnableTick();
}

void ACpp_BoatBase::UpdateActorRotation()
{
	const auto rotation = GetActorRotation();
	auto velocity = GetVelocity();
	velocity = FVector(FMath::Abs(velocity.X), velocity.Y, velocity.Z);
	const auto lerp = FMath::Lerp(rotation, velocity.Rotation(), 0.1);
	const auto finalRot = FRotator(rotation.Pitch, lerp.Yaw, rotation.Roll);
	SetActorRotation(finalRot);
}


void ACpp_BoatBase::ConstructBoatBuoyancy(TArray<UArrowComponent*> Components)
{
	for (const auto Component : Components)
	{
		FSphericalPontoon pontoon = FSphericalPontoon();
		pontoon.RelativeLocation = Component->GetRelativeLocation();
		pontoon.Radius = 100;
		BuoyancyComponent->BuoyancyData.Pontoons.Add(pontoon);
	}
	BuoyancyComponent->BuoyancyData.bApplyDragForcesInWater = true;
}

