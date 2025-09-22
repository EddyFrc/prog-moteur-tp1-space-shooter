// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter/Public/Spaceship.h"

// ----- MÉTHODES -----

int ASpaceship::GetHealth()
{
	return Health;
}

void ASpaceship::TakeHit(const FVector& HitForce)
{
	Health--;
	GetCapsuleComponent()->AddImpulse(HitForce, NAME_None, true);
}

void ASpaceship::SetDirection(const FRotator& Rotation)
{
	GetRootComponent()->SetRelativeRotation(Rotation);
}

void ASpaceship::Shoot()
{
	GetWorld()->SpawnActor<AActor>(ProjectileClass, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
}

// ----- REDÉFINITIONS et CONSTRUCTEUR -----

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

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

// Sets default values
ASpaceship::ASpaceship()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
