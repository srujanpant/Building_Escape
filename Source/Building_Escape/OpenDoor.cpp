// Copyright 2021, Srujan Pant. All Rights Reserved.

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	OpenAngle = 90.f;
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw = InitialYaw + OpenAngle;

	FindPressurePlate();
	FindAudioComponent();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TotalMassOfActors() > MassToOpenDoors)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}	
	else
	{	
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if(CurrentTime - DoorLastOpened > DoorCloseDelay)
		{	
			CloseDoor(DeltaTime);
		}	
	}
}

//User Defined Function
void UOpenDoor::OpenDoor(float DeltaTime)
{
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator OpenDoor(0.f,0.f,0.f);

	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw,TargetYaw,DeltaTime,2);
	GetOwner()->SetActorRotation(OpenDoor);

	CloseDoorSound = false;
	if(!AudioComponent)
	{
		return;
	}

	if(!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator CloseDoor(0.f,0.f,0.f);

	CloseDoor.Yaw = FMath::FInterpTo(CurrentYaw,InitialYaw,DeltaTime,2);
	GetOwner()->SetActorRotation(CloseDoor);

	OpenDoorSound = false;
	if(!AudioComponent)
	{
		return;
	}

	if(!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpenDoor::TotalMassOfActors()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if(!PressurePlate)
	{
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* i : OverlappingActors)
	{
		TotalMass += i->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if(!AudioComponent)
	{
		UE_LOG(LogTemp,Error,TEXT("Audio component not found on %s!"), *GetOwner()->GetName()); 
	}
}

void UOpenDoor::FindPressurePlate()
{
	if(!PressurePlate)
	{
		UE_LOG(LogTemp,Error,TEXT("%s has the door component on it, BUT, the PressurePlate component has not been set!"), *GetOwner()->GetName());
	}
}