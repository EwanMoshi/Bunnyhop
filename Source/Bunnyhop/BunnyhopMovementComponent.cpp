// Fill out your copyright notice in the Description page of Project Settings.


#include "BunnyhopMovementComponent.h"

#include "BunnyhopCharacter.h"
#include "DrawDebugHelpers.h"

UBunnyhopMovementComponent::UBunnyhopMovementComponent()
{
	GroundFriction = 2800.0f;
	JumpZVelocity = 500.0f;
}

void UBunnyhopMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ownerLocation = GetOwner()->GetActorLocation();
	FVector ownerVelocity = GetOwner()->GetVelocity();

	// scale velocity to draw debug line
	FVector scaledOwnerVelocity = ownerVelocity * 0.3f;
	
	
	//GetLastUpdateVelocity()
	DrawDebugLine(GetWorld(), ownerLocation, ownerLocation + scaledOwnerVelocity, FColor::Emerald, false, 0.05f, 0, 2.0f);

	WishDirection = ConsumeInputVector();
	UE_LOG(LogTemp, Warning, TEXT("inputVector: %s"), *WishDirection.ToString());

	DrawDebugLine(GetWorld(), ownerLocation, ownerLocation + WishDirection * 5.0f, FColor::Blue, false, 0.05f, 0, 2.0f);

	WishDirection.Normalize();
	PerformMovement(DeltaTime);
}

void UBunnyhopMovementComponent::PerformMovement(float DeltaTime)
{
	TryJump();

	// crouch?

	if (IsMovingOnGround())
	{
		ApplyGroundFriction(DeltaTime);
		Accelerate(WishDirection, WalkSpeed, WalkAcceleration, DeltaTime);
	}
	else
	{
		Accelerate(WishDirection, AirSpeed, AirAcceleration, DeltaTime);
		Velocity.Z += GetGravityZ() * DeltaTime;
	}

	ApplyMove(DeltaTime);
}

void UBunnyhopMovementComponent::ApplyGroundFriction(float DeltaTime)
{
	float CurrentSpeed = Velocity.Size();

	if (CurrentSpeed == 0)
	{
		return;
	}

	float VelocityDrop = GroundFriction * DeltaTime;
	float NewSpeed = CurrentSpeed - VelocityDrop;

	if (NewSpeed < 0)
    {
    	NewSpeed = 0;
    }

	Velocity = Velocity * (NewSpeed / CurrentSpeed);
}

void UBunnyhopMovementComponent::ApplyMove(float DeltaTime)
{
	FVector MovementVector = Velocity * DeltaTime;
	
	if (!MovementVector.IsNearlyZero())
	{
		FHitResult hit;
		SafeMoveUpdatedComponent(MovementVector, UpdatedComponent->GetComponentRotation(), true,hit);

		if (hit.IsValidBlockingHit())
		{
			// no sliding logic
			SetMovementMode(MOVE_Walking);
		}
	}
}

void UBunnyhopMovementComponent::Accelerate(FVector WishDir, float WishSpeed, float Accel, float DeltaTime)
{
	auto CurrentSpeed = FVector::DotProduct(Velocity, WishDir);

	float AddSpeed = WishSpeed - CurrentSpeed;

	if (AddSpeed <= 0)
	{
		return;
	}

	float AccelerationSpeed = Accel * WishSpeed * DeltaTime;

	if (AccelerationSpeed > AddSpeed)
	{
		AccelerationSpeed = AddSpeed;
	}
	
	Velocity = Velocity + AccelerationSpeed * WishDir;
}


void UBunnyhopMovementComponent::TryJump()
{
	if (IsMovingOnGround())
	{
		auto OwnerChar = Cast<ABunnyhopCharacter>(GetOwner());
		
		if (OwnerChar)
		{
			if (OwnerChar->jumpPressed)
			{
				Velocity.Z += JumpZVelocity;
				SetMovementMode(MOVE_Flying);
			}
		}
	}
}

