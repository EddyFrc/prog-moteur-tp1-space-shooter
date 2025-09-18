// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/VolumePawn.h"

#include "GameFramework/FloatingPawnMovement.h"

// ----- GETTERS -----

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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Format(TEXT("Apply force X={0} Y={1} Z={2}"), {Force.X, Force.Y, Force.Z}));
	GetPawnMovementComponent()->AddInputVector(Force);
}

void AVolumePawn::Move(const FVector& Direction)
{
	FVector ActualForce = FVector(Direction);
	ActualForce.Normalize();
	ActualForce *= GetPawnMovementComponent()->GetMaxSpeed();
	ActualForce = ActualForce.GetClampedToMaxSize(GetPawnMovementComponent()->GetMaxSpeed());
	ApplyForce(ActualForce);
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
}
