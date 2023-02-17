// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//get player character
	this->targetCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//get player character every frame
	//ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(this,0);

	//Look at the player character every frame
	LookAtActor(targetCharacter);


}

void AEnemyCharacter::LookAtActor(AActor* targetActor)
{
	if (targetActor == nullptr)
	{
		return;
	}

	if (CanSeeActor(targetActor))
	{
		//FVector Holds x,y,z location

		//Sets the location of enemy and the target
		FVector start = GetActorLocation();
		FVector end = targetActor->GetActorLocation();

		//Calculate rotation for start point to face the end point
		FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(start,end);

		//Set enemys rotation to that rotation
		SetActorRotation(lookAtRotation);
	}
}

//Using line casting (raycasting) to check if this enemy is blocked by something
bool AEnemyCharacter::CanSeeActor(const AActor* const targetActor) const
{
	if (targetActor == nullptr)
	{
		return false;
	}

	//Store results of line trace
	FHitResult hit;

	//Storing line trace start and end points
	FVector start = GetActorLocation();
	FVector end = targetActor->GetActorLocation();

	//Trace channel we want to compare against. Using visibility trace channel.
	ECollisionChannel channel = ECollisionChannel::ECC_Visibility;


	FCollisionQueryParams queryParams;

	//Ignore the actor that's executing this line trace
	queryParams.AddIgnoredActor(this);

	//Also ignore the target we're checking for
	queryParams.AddIgnoredActor(targetActor);

	//Execute the line trace
	GetWorld()->LineTraceSingleByChannel(hit, start, end, channel, queryParams);

	//Set color of line trace to green if blocked or red if not blocked
	FColor lineColor = (hit.bBlockingHit) ? FColor::Green : FColor::Red;

	//Show the line trace inside the game
	DrawDebugLine(GetWorld(), start, end, lineColor);
	
	return !hit.bBlockingHit;
}


