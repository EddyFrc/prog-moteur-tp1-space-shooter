// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SpaceShooterLevel.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASpaceShooterLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	bool IsGameRunning;
	FTimerHandle ObstacleSpawnTimer;

	UPROPERTY(EditAnywhere)
	UClass* DefaultObstacleClass;

	void OnObstacleSpawn();

protected:
	virtual void BeginPlay() override;
};
