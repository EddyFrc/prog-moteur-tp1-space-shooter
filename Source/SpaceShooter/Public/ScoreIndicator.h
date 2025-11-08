// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "ScoreIndicator.generated.h"

UCLASS()
class SPACESHOOTER_API AScoreIndicator : public AActor
{
	GENERATED_BODY()

	FString Label;
	uint64 SpawnFrame;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* LabelComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* RootStaticMesh;

	void SetLabel(const FString& InLabel);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AScoreIndicator();
};
