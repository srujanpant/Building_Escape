// Copyright 2021, Srujan Pant. All Rights Reserved.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("%s  %f"), *GetOwner()->GetActorRotation().ToString(), GetOwner()->GetActorRotation().Yaw);

	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator OpenDoor(0.f,0.f,0.f);
	float TargetYaw = InitialYaw + OpenAngle;

	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw,TargetYaw,DeltaTime,2);
	GetOwner()->SetActorRotation(OpenDoor);

}

