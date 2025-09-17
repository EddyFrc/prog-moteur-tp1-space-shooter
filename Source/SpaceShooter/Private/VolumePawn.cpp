// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/VolumePawn.h"

URotatingMovementComponent* AVolumePawn::GetRotatingMovementComponent()
{
	return RotatingMovementComponent;
}

UPawnMovementComponent* AVolumePawn::GetPawnMovementComponent()
{
	return PawnMovementComponent;
}

UStaticMeshComponent* AVolumePawn::GetStaticMeshComponent()
{
	return StaticMeshComponent;
}

UCapsuleComponent* AVolumePawn::GetCapsuleComponent()
{
	return CapsuleComponent;
}

// Called when the game starts or when spawned
void AVolumePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVolumePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVolumePawn::ApplyForce(const FVector& Force)
{
	GetPawnMovementComponent()->AddInputVector(Force);
}

void AVolumePawn::Move(const FVector& Direction)
{
	FVector ActualForce = FVector(Direction);
	ActualForce.Normalize();
	ActualForce *= GetPawnMovementComponent()->Velocity;
	ActualForce = ActualForce.GetClampedToMaxSize(GetPawnMovementComponent()->GetMaxSpeed());
	ApplyForce(ActualForce);
}

void AVolumePawn::ApplyRotationForce(const FRotator& Rotation)
{
	GetRotatingMovementComponent()->RotationRate = Rotation;
}

// Called to bind functionality to input
void AVolumePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Sets default values
AVolumePawn::AVolumePawn()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	CapsuleComponent->SetupAttachment(CapsuleComponent);

	PawnMovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(
		TEXT("PawnMovementComponent"));
	PawnMovementComponent->UpdatedComponent = CapsuleComponent;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->UpdatedComponent = CapsuleComponent;
}
