// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/VolumePawn.h"

// ----- GETTERS -----

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

// ----- MÉTHODES -----

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

// ----- REDÉFINITIONS et CONSTRUCTEUR -----

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
	RootComponent = GetCapsuleComponent();

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	GetStaticMeshComponent()->SetupAttachment(GetCapsuleComponent());

	PawnMovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(
		TEXT("PawnMovementComponent"));
	GetPawnMovementComponent()->UpdatedComponent = GetCapsuleComponent();

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	GetRotatingMovementComponent()->UpdatedComponent = GetCapsuleComponent();
}
