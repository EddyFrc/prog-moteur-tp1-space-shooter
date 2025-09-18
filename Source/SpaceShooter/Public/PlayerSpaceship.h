// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Spaceship.h"
#include "PlayerSpaceship.generated.h"

UCLASS()
class SPACESHOOTER_API APlayerSpaceship : public ASpaceship
{
	GENERATED_BODY()

	// ----- ATTRIBUTS -----

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* ShootAction;

	// ----- MÉTHODES -----

public:
	UFUNCTION(BlueprintCallable)
	void MoveFromInput(const FVector2D& Input);

	void OnMoveAction(const FInputActionInstance& Instance);

	void OnShootAction(const FInputActionInstance& Instance);

	// ----- REDÉFINITIONS et CONSTRUCTEUR -----

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	APlayerSpaceship();
};
