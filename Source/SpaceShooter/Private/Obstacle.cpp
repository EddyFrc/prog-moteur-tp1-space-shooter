// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"

#include "PlayerSpaceship.h"

void AObstacle::OnBeginOverlap(AActor* Myself, AActor* OtherActor)
{
	if (APlayerSpaceship* Player = Cast<APlayerSpaceship>(OtherActor))
	{
		Player->TakeHit();
		OnObstacleDestroy();
	}
}

void AObstacle::ApplyRandomPathWorker(double X, double Y, int MinYaw, int MaxYaw)
{
	StaticMeshComponent->SetWorldLocation(FVector(X, Y, 0));
	StaticMeshComponent->
		SetPhysicsLinearVelocity(FRotator(0, FMath::RandRange(MinYaw, MaxYaw), 0).Vector() * FMath::RandRange(100, 200),
		                         false);
}

void AObstacle::ApplyRandomPath()
{
	RotatingMovementComponent->RotationRate = FRotator(FMath::RandHelper(180), FMath::RandHelper(180),
	                                                   FMath::RandHelper(180));
	int Seed = FMath::RandHelper(7);
	switch (Seed)
	{
	case 0:
		ApplyRandomPathWorker(750, 0, 135, 225);
		break;
	case 1:
		ApplyRandomPathWorker(750, 1070, 200, 240);
		break;
	case 2:
		ApplyRandomPathWorker(0, 1070, 260, 280);
		break;
	case 3:
		ApplyRandomPathWorker(-750, 1070, 280, 330);
		break;
	case 4:
		ApplyRandomPathWorker(-750, 0, -50, 40);
		break;
	case 5:
		ApplyRandomPathWorker(-750, -1070, 20, 70);
		break;
	case 6:
		ApplyRandomPathWorker(0, -1070, 60, 110);
		break;
	default:
		ApplyRandomPathWorker(-750, 0, 105, 145);
	}
}

void AObstacle::TakeHit()
{
	Health--;
	if (Health <= 0)
	{
		OnObstacleDestroy();
	}
}

void AObstacle::OnObstacleDestroy()
{
	Destroy();
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	ApplyRandomPath();
	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Sets default values
AObstacle::AObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(CapsuleComponent);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->UpdatedComponent = StaticMeshComponent;
}
