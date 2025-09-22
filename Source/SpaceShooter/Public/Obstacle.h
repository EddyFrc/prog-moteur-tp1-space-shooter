// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "SpaceShooterLevel.h"
#include "Obstacle.generated.h"

UCLASS()
class SPACESHOOTER_API AObstacle : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URotatingMovementComponent* RotatingMovementComponent;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* Particle;

	UPROPERTY()
	UNiagaraComponent* ParticleComponent;

	UPROPERTY()
	ASpaceShooterLevel* SpaceShooterLevelScript;
	

protected:
	double Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	int Health;
	int MaxHealth;
	// Instant du premier TakeHit (premier projectile reçu), pas défini si pas encore touché
	FDateTime FirstHitTimestamp;
	// Nombre de millisecondes entre le premier TakeHit et le dernier (celui qui détruit l'astéroide)
	double TotalTimeToDestroy;

	UFUNCTION()
	void OnBeginOverlap(AActor* Myself, AActor* OtherActor);

public:
	UFUNCTION()
	void ApplyRandomPathWorker(double X, double Y, int MinYaw, int MaxYaw);

	UFUNCTION(BlueprintCallable)
	void ApplyRandomPath();

	UFUNCTION()
	void TakeHit();

	UFUNCTION()
	void OnObstacleDestroy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AObstacle();
};
