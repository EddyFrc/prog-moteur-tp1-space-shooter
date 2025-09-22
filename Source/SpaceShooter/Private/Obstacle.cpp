// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"

#include "NiagaraFunctionLibrary.h"
#include "PlayerSpaceship.h"
#include "GameFramework/KillZVolume.h"

void AObstacle::OnBeginOverlap(AActor* Myself, AActor* OtherActor)
{
	// Check si c'est le joueur et qu'il n'est pas invincible
	if (APlayerSpaceship* Player = Cast<APlayerSpaceship>(OtherActor);
		Player
		&& !Player->IsInvincible
		&& StaticMeshComponent->IsVisible())
	{
		// Toucher le joueur et appliquer une force par la même occasion
		Player->TakeHit((Player->GetActorLocation() - StaticMeshComponent->GetComponentLocation()) * 10);
		OnObstacleDestroy();
	}
	else if (Cast<AKillZVolume>(OtherActor))
	{
		Destroy();
	}
}

void AObstacle::ApplyRandomPathWorker(double X, double Y, int MinYaw, int MaxYaw)
{
	StaticMeshComponent->SetWorldLocation(FVector(X, Y, 0));
	StaticMeshComponent->
		SetPhysicsLinearVelocity(FRotator(0, FMath::RandRange(MinYaw, MaxYaw), 0).Vector() * FMath::RandRange(100, 400),
		                         false);
}

void AObstacle::ApplyRandomPath()
{
	// Applique une rotation aléatoire 
	RotatingMovementComponent->RotationRate = FRotator(FMath::RandHelper(120), FMath::RandHelper(120),
	                                                   FMath::RandHelper(120));
	// 8 endroits d'où un obstacle peut spawner, avec chacun leur coordonnées et angles de départ
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
	if (Particle)
	{
		StaticMeshComponent->SetVisibility(false);
		ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), Particle, StaticMeshComponent->GetComponentLocation());
	}
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

	if (FMath::Abs(StaticMeshComponent->GetComponentLocation().X) > 1100
		|| FMath::Abs(StaticMeshComponent->GetComponentLocation().Y) > 800)
	{
		Destroy();
	}
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

	Scale = FMath::RandRange(0.004, 0.01);
	StaticMeshComponent->SetWorldScale3D(FVector(Scale, Scale, Scale));

	Health = FMath::RandRange(5, 10);
}
