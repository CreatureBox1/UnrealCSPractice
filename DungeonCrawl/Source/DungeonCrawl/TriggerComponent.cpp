// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"
#include "Grabber.h"
#include "WallMover.h"


// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent = GetOwner()->FindComponentByClass<UBoxComponent>();
	
	if (WallToMove == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wall To Move not set on trigger component!"));
	}

	WallMover = WallToMove->FindComponentByClass<UWallMover>();

}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BoxComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("A box component is required for the trigger component!"));
	}

	TArray<AActor*> Actors;
	BoxComponent->GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		//FString ActorName = Actor->GetActorNameOrLabel();

		if (Actor->ActorHasTag("OpenDoor1") && WallMover->MoveTriggered == false)
		{
			Player->FindComponentByClass<UGrabber>()->Release();
			
			UPrimitiveComponent* comp = Actor->FindComponentByClass<UPrimitiveComponent>();
			
			comp->SetSimulatePhysics(false);

			Actor->SetActorLocation(BoxComponent->GetComponentLocation() - FVector(0,0,30));
			WallMover->SetMoveTriggered(true);
		}

	}
}

