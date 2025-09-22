// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterLevel.h"

#include "Microsoft/AllowMicrosoftPlatformTypes.h"

void ASpaceShooterLevel::OnObstacleSpawn()
{
	if (IsGameRunning)
	{
		GetWorld()->SpawnActor<AActor>(DefaultObstacleClass, FVector(2000, 2000, 0), FRotator(0, 0, 0));
	}
}

void ASpaceShooterLevel::BeginPlay()
{
	Score = 0;
	Super::BeginPlay();
	IsGameRunning = true;

	GetWorldTimerManager().SetTimer(ObstacleSpawnTimer, this, &ThisClass::OnObstacleSpawn, 0.2f, true);
}

FString ASpaceShooterLevel::GetScoreText()
{
	return FString::Printf(TEXT("%d"), Score);
}
