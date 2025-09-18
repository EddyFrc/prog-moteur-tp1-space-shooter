// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"
#include "EnhancedInputComponent.h"

// ----- MÉTHODES

void APlayerSpaceship::MoveFromInput(const FVector2D& Input)
{
	// Construire la rotation correspondante pour tourner le vaisseau
	FRotator CorrespondingRotation = FVector(Input.X, Input.Y, 0).Rotation();
	// Ces méthodes sont héritées, voir Spaceship et VolumePawn
	SetDirection(CorrespondingRotation);
	MoveForward();
}

void APlayerSpaceship::OnMoveAction(const FInputActionInstance& Instance)
{
	MoveFromInput(Instance.GetValue().Get<FVector2D>());
}

void APlayerSpaceship::OnShootAction(const FInputActionInstance& Instance)
{
	if (Instance.GetValue().Get<bool>())
	{
		Shoot();
	}
}

// ----- REDÉFINITIONS et CONSTRUCTEUR -----

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerSpaceship::OnMoveAction);
	Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerSpaceship::OnShootAction);
}


// Sets default values
APlayerSpaceship::APlayerSpaceship()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Auto possess player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}
