// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/Spaceship.h"


// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceship::SetRotation(const FRotator& Rotation)
{
	GetRootComponent()->SetRelativeRotation(Rotation);
}

void ASpaceship::MoveForward()
{
	Move(GetActorRotation().Vector());
}

void ASpaceship::Shoot()
{
	GetWorld()->SpawnActor<AActor>(ProjectileClass, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Sets default values
ASpaceship::ASpaceship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
