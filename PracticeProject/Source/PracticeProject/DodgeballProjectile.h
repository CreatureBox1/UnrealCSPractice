// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class PRACTICEPROJECT_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Dodgeball Sound
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* DamageSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundAttenuation* BounceSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = Particles)
		class UParticleSystem* HitParticles;


public:	
	ADodgeballProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

};
