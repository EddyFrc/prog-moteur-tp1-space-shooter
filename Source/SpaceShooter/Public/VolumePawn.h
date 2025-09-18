// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "VolumePawn.generated.h"

UCLASS()
class SPACESHOOTER_API AVolumePawn : public APawn
{
	GENERATED_BODY()

	// ----- ATTRIBUTS -----

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* PawnMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URotatingMovementComponent* RotatingMovementComponent;

protected:
	// ----- GETTERS -----

	UFUNCTION(BlueprintCallable)
	URotatingMovementComponent* GetRotatingMovementComponent();

	UFUNCTION(BlueprintCallable)
	UPawnMovementComponent* GetPawnMovementComponent();

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetStaticMeshComponent();

	UFUNCTION(BlueprintCallable)
	UCapsuleComponent* GetCapsuleComponent();

	// ----- MÉTHODES -----

	/**
	 * Applique la force voulue au pion
	 * 
	 * À appeler à chaque frame
	 * @param Force Vecteur représentant la force à appliquer
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyForce(const FVector& Force);

	/**
	 * Applique une force dans la direction voulue
	 * 
	 * La force réelle appliquée sera basée sur la vitesse et vitesse max
	 * du MovementComponent de ce pion
	 * @param Direction Vecteur représentant une direction
	 */
	UFUNCTION(BlueprintCallable)
	void Move(const FVector& Direction);

	/**
	 * Définit une force de rotation constante
	 * @param Rotation FRotator représentant la force de rotation à appliquer
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyRotationForce(const FRotator& Rotation);

	// ----- REDÉFINITIONS et CONSTRUCTEUR -----

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	AVolumePawn();
};
