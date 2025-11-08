// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreIndicator.h"


void AScoreIndicator::SetLabel(const FString& InLabel)
{
	Label = FString(InLabel);
	LabelComponent->SetText(FText::FromString(Label));
}


// Called when the game starts or when spawned
void AScoreIndicator::BeginPlay()
{
	Super::BeginPlay();
	SpawnFrame = GFrameCounter;
	RootStaticMesh->SetPhysicsLinearVelocity(FVector(300, 0, 0), false);
}

// Called every frame
void AScoreIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GFrameCounter - 40 > SpawnFrame)
	{
		Destroy();
	}
}


// Sets default values
AScoreIndicator::AScoreIndicator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootStaticMesh"));
	RootComponent = RootStaticMesh;

	LabelComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LabelComponent"));
	LabelComponent->SetupAttachment(RootStaticMesh);
}
