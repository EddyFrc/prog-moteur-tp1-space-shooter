// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"
#include "EnhancedInputComponent.h"
#include "MovieSceneTracksComponentTypes.h"
#include "SpaceShooterLevel.h"
#include "Kismet/GameplayStatics.h"

// ----- MÉTHODES

void APlayerSpaceship::MoveFromInput(const FVector2D& Input)
{
	// Construire la rotation correspondante pour tourner le vaisseau
	FRotator CorrespondingRotation = FVector(Input.X, Input.Y, 0).Rotation();
	// Ces méthodes sont héritées, voir Spaceship et VolumePawn
	SetDirection(CorrespondingRotation);
	MoveForward();
}

bool APlayerSpaceship::IsHeartFull(const int HeartIndex) const
{
	return Health > HeartIndex;
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

void APlayerSpaceship::UnsetInvincibility()
{
	IsInvincible = false;
	GetStaticMeshComponent()->SetVisibility(true, false);
}


// ----- REDÉFINITIONS et CONSTRUCTEUR -----

void APlayerSpaceship::TakeHit(const FVector& HitForce)
{
	Super::TakeHit(HitForce);
	IsInvincible = true;
	GetWorldTimerManager().SetTimer(InvincibilityTimer, this, &APlayerSpaceship::UnsetInvincibility, 3);
	if (Health <= 0)
	{
		OnSpaceshipDestroyed();
	}
}

void APlayerSpaceship::OnSpaceshipDestroyed_Implementation()
{
	Cast<ASpaceShooterLevel>(GetWorld()->GetLevelScriptActor())->IsGameRunning = false;
}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(0, 0, 0));
}

// Called every frame
void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsInvincible && GFrameCounter % 3 == 0)
	{
		GetStaticMeshComponent()->ToggleVisibility(false);
	}
}

// Called to bind functionality to input
void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerSpaceship::OnMoveAction);
	Input->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerSpaceship::OnShootAction);
}


// Sets default values
APlayerSpaceship::APlayerSpaceship()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcess->SetupAttachment(GetCapsuleComponent());
}
