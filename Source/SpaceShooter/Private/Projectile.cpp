// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ActualDirection = GetActorRotation().Vector();
	ActualDirection.Normalize();
	ActualDirection *= 2000;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Tick");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Format(TEXT("GetActorForwardVector({0}, {1}, {2})"), {ActualDirection.X, ActualDirection.Y, ActualDirection.Z}));
	CapsuleComponent->SetPhysicsLinearVelocity(ActualDirection, false);
	
}

// Sets default values
AProjectile::AProjectile()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(CapsuleComponent);
}
