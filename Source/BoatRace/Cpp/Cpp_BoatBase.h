// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuoyancyComponent.h"
#include "Components/ArrowComponent.h"
#include "Cpp_BoatBase.generated.h"

UCLASS()
class BOATRACE_API ACpp_BoatBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACpp_BoatBase();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	UBuoyancyComponent* BuoyancyComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	UStaticMeshComponent* BoatMesh;

	// Boat Properties
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BoatProperties")
	float ForwardSpeed = 1.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BoatProperties")
	float TurningSpeed = 1.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="BoatProperties")
	float MaximumSpeed = 2000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void AddMovementForce(float Value, float Speed, FVector Direction);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Buoyancy")
	void ConstructBoatBuoyancy(TArray<UArrowComponent*> Components);
};
