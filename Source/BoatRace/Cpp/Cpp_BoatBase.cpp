// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_BoatBase.h"

#include "BoatRace/Statics/Utils.h"

// Sets default values
ACpp_BoatBase::ACpp_BoatBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuoyancyComponent = CreateDefaultSubobject<UBuoyancyComponent>("Buoyancy");
	BoatMesh = CreateDefaultSubobject<UStaticMeshComponent>("BoatMesh");
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

void ACpp_BoatBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACpp_BoatBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACpp_BoatBase::MoveRight);
}

void ACpp_BoatBase::MoveForward(float Value)
{
	AddMovementForce(Value, ForwardSpeed, GetActorForwardVector());
}

void ACpp_BoatBase::MoveRight(float Value)
{
	AddMovementForce(Value, TurningSpeed, GetActorRightVector());
	auto rotation = GetActorRotation();
	const auto rotateSpeed = Value * TurningSpeed * 0.3f;
	rotation.Yaw += rotateSpeed;
	SetActorRelativeRotation(rotation);
}

void ACpp_BoatBase::AddMovementForce(float Value, float Speed, FVector Direction)
{
	if (GetVelocity().Size() < MaximumSpeed)
	{
		const auto force = Value * Speed * 500.0f;
		const auto directionForce = force * Direction;
		BoatMesh->AddForce(directionForce, "", true);
	}
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
