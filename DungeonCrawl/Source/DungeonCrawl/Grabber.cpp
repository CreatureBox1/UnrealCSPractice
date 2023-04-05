// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{

	if (PhysicsHandle == nullptr)
	{
		return;
	}

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
	bool HasHit = GetWorld()->SweepSingleByChannel(hit, StartPos, EndPos, FQuat::Identity,
		ECC_GameTraceChannel2, SphereShape);

	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = hit.GetComponent();
		//Physics objects not moved for a while will go to sleep. 
		//Have to wake them up again so they can be picked up.
		HitComponent->WakeAllRigidBodies();

		PhysicsHandle->GrabComponentAtLocationWithRotation
		(
			HitComponent, //Component that was hit
			NAME_None, //Used when we dont want to specify a name
			hit.ImpactPoint, //Location where we want to grab the object
			GetComponentRotation() //We will use the rotation of the grabber
		);

	}


	//Debug
	
	//if (HasHit)
	//{
	//	//Location of sphere when it impacts
	//	DrawDebugSphere(GetWorld(), hit.Location, 10, 10, FColor::Green, false, 10);

	//	//Where the sphere impacts the target
	//	DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10, 10, FColor::Red, false, 10);
	//	FString HitActorName = hit.GetActor()->GetActorNameOrLabel();
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Display, TEXT("No actor hit!"));
	//}
}

void UGrabber::Release()
{
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

