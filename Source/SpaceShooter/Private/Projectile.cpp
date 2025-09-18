// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Direction = GetActorRotation().Vector();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Format(TEXT("Actor rotation vector = ({0}, {1}, {2})"), {Direction.X, Direction.Y, Direction.Z}));
	Move(GetActorRotation().Vector());
}

// Called to bind functionality to input
void AProjectile::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Sets default values
AProjectile::AProjectile()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
