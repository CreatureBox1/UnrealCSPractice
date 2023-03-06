// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICEPROJECT_API UMoveActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveActor(float DeltaTime);

	void RotateActor(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Move Actor Component")
		FVector moveVelocity = FVector(100, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Move Actor Component")
		FRotator rotationVelocity;

	UPROPERTY(EditAnywhere, Category = "Move Actor Component")
		float moveDistance = 100;


private:
	UPROPERTY(VisibleAnywhere, Category = "Move Actor Component")
	FVector startLocation;

	

};
