// Copyright 2021, Srujan Pant. All Rights Reserved.


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

	/*
	1) Create a trigger Volume
	2) Inheret it in the pickup object
	3) Make EditAnywhere of pawn Actor and PressurePlate
	4) TriggerPad contact gives console Log message that you can pick up the object
	5) Assign E button to pickup
	6) Get the default pawn Actor using code and use Actor position relative to function (or some other function with the same functionality) to transport the object relative to the default pawn
	7) Set Actor Location could be used for the transform operation
	*/
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

