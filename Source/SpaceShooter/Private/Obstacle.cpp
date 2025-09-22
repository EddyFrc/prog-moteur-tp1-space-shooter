// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"

#include "NiagaraFunctionLibrary.h"
#include "PlayerSpaceship.h"
#include "SpaceShooterLevel.h"
#include "Engine/LevelScriptActor.h"
#include "GameFramework/KillZVolume.h"
#include "Math/UnitConversion.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"

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
	StaticMeshComponent->SetMaterial(0, HitMaterial);
	LastHitFrame = GFrameCounter;
	if (Health == MaxHealth)
	{
		FirstHitTimestamp = FDateTime::Now();
	}
	Health--;
	SpaceShooterLevelScript->Score += 50;
	SpaceShooterLevelScript->Score += (MaxHealth - Health) * 5;
	if (Health <= 0)
	{
		// Calcul du temps total pour détruire l'astéroide
		TotalTimeToDestroy = (FDateTime::Now() - FirstHitTimestamp).GetTotalMilliseconds();
		// Plus ce temps est bas plus le bonus est élevé
		if (TotalTimeToDestroy < 5000)
			SpaceShooterLevelScript->Score += (5000 - TotalTimeToDestroy) / 3;
		// Dans tous les cas on gagne 1000
		SpaceShooterLevelScript->Score += 1000;
		OnObstacleDestroy();
	}
}

void AObstacle::OnObstacleDestroy()
{
	if (Particle)
	{
		ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), Particle, StaticMeshComponent->GetComponentLocation());
	}
	Destroy();
}


// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	SpaceShooterLevelScript = Cast<ASpaceShooterLevel>(GetWorld()->GetLevelScriptActor());
	Scale = FMath::RandRange(0.004f, 0.01f);
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Format(TEXT("Scale = {0}"), {Scale}));
	StaticMeshComponent->SetRelativeScale3D(FVector(Scale, Scale, Scale));
	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	Health = FMath::RandRange(5, 10);
	MaxHealth = Health;
	LastHitFrame = 0;
	ApplyRandomPath();

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

	if (LastHitFrame < GFrameCounter - 5)
	{
		StaticMeshComponent->SetMaterial(0, RegularMaterial);
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

}
