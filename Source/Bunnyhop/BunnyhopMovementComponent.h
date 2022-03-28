// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BunnyhopMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BUNNYHOP_API UBunnyhopMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UBunnyhopMovementComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PerformMovement(float DeltaTime) override;
	virtual void AddInputVector(FVector WorldVector, bool bForce) override;
	
	void ApplyMove(float DeltaTime);
	void MoveGround(float DeltaTime);
	void ApplyGroundFriction(float DeltaTime);
	void Accelerate(FVector WishDir, float WishSpeed, float Accel, float DeltaTime);
	void TryJump();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector WishDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WalkSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WalkAcceleration = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AirSpeed = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AirAcceleration = 9000.0f;

private:
	bool IsJumpHeldDown();
};
