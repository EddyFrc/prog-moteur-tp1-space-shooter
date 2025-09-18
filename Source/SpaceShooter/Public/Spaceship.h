// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VolumePawn.h"
#include "Spaceship.generated.h"

UCLASS()
class SPACESHOOTER_API ASpaceship : public AVolumePawn
{
	GENERATED_BODY()

	// ----- ATTRIBUTS -----

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ProjectileClass;

	// ----- MÉTHODES -----

protected:
	UFUNCTION(BlueprintCallable)
	virtual void OnSpaceshipDestroyed();

public:
	UFUNCTION(BlueprintCallable)
	int GetHealth();

	UFUNCTION(BlueprintCallable)
	void TakeHit();

	/**
	 * Change la direction du vaisseau
	 * @param Rotation Angle à appliquer
	 */
	UFUNCTION(BlueprintCallable)
	void SetDirection(const FRotator& Rotation);

	/**
	 * Génère un projectile selon la classe définie dans ProjectileClass
	 */
	UFUNCTION(BlueprintCallable)
	void Shoot();

	// ----- REDÉFINITIONS et CONSTRUCTEUR -----

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this pawn's properties
	ASpaceship();
};
