// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActorComponent.h"

// Sets default values for this component's properties
UMoveActorComponent::UMoveActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetOwner()->GetActorLocation();

	// Outputting variables to the console test:

	/*FString actorName = GetOwner()->GetActorNameOrLabel();

	FString positionOfActor = GetOwner()->GetActorLocation().ToString();
	

	UE_LOG(LogTemp, Warning, TEXT("Actor %s is at location %s"), *actorName, *positionOfActor);*/

}


// Called every frame
void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//---------Move Actor-----------
	
	MoveActor(DeltaTime);
	RotateActor(DeltaTime);
}

void UMoveActorComponent::MoveActor(float DeltaTime)
{
	//Get Current Location
	FVector currentLocation = GetOwner()->GetActorLocation();

	//Add Vector to Location
	currentLocation += moveVelocity * DeltaTime;

	GetOwner()->SetActorLocation(currentLocation);

	float distanceMoved = FVector::Distance(startLocation, currentLocation);

	//Reverse direction if moved far enough
	if (distanceMoved >= moveDistance)
	{
		FVector moveDirection = moveVelocity.GetSafeNormal();

		//set start location to end location
		startLocation += moveDirection * moveDistance;
		GetOwner()->SetActorLocation(startLocation);

		//reverse velocity
		moveVelocity = -moveVelocity;
	}
}

void UMoveActorComponent::RotateActor(float DeltaTime)
{
	GetOwner()->AddActorLocalRotation(rotationVelocity * DeltaTime);
}

