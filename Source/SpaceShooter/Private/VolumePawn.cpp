// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/VolumePawn.h"


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

void AVolumePawn::MoveForward(double ForwardForce)
{
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
