// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VolumePawn.h"
#include "Spaceship.generated.h"

UCLASS()
class SPACESHOOTER_API ASpaceship : public AVolumePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ProjectileClass;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Change la direction du vaisseau
	 * @param Rotation Angle à appliquer
	 */
	UFUNCTION(BlueprintCallable)
	void SetRotation(const FRotator& Rotation);

	/**
	 * Fait se déplacer le vaisseau vers l'avant
	 *
	 * À appeler à chaque frame
	 */
	UFUNCTION(BlueprintCallable)
	void MoveForward();

	UFUNCTION(BlueprintCallable)
	void Shoot();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	ASpaceship();
};
