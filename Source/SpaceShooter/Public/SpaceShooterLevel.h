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

	int Score;

	UPROPERTY(EditAnywhere)
	UClass* DefaultObstacleClass;

	void OnObstacleSpawn();

	UFUNCTION(BlueprintCallable)
	FString GetScoreText();

protected:
	virtual void BeginPlay() override;
};
