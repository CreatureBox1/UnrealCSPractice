// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FRotator MyRotation = GetComponentRotation();
	
	//Drawing a debug line forward from player
	FVector StartPos = GetComponentLocation();
	FVector EndPos = StartPos + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red);

	//Creating a geometry sphere sweep
	//Trace Channel for Grabber: ECC_GameTraceChannel2
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(GrabRadius);

	//A variable to hold the results of the sweep
	FHitResult hit;

	//Geometry Sweep 
	bool HasHit = GetWorld()->SweepSingleByChannel(hit,StartPos,EndPos,FQuat::Identity,
													ECC_GameTraceChannel2, SphereShape);

	if (HasHit)
	{
		FString HitActorName = hit.GetActor()->GetActorNameOrLabel();

	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No actor hit!"));
	}

}

