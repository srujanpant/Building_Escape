// Copyright 2021, Srujan Pant. All Rights Reserved.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Calling checking functions
	FindPhysicsHandle();
	CheckInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!PhysicsHandle)
	{
		return;
	}

	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetObject();
	UPrimitiveComponent* GrabComponent = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if(ActorHit)
	{
		if(!PhysicsHandle)
		{
			return;
		}
		//PhysicsHandle->GrabComponentAtLocation(GrabComponent, NAME_None, GetPlayerReach());
		PhysicsHandle->GrabComponentAtLocationWithRotation(GrabComponent, NAME_None, GetPlayerReach(), GetPlayerRotation());
	}
}

void UGrabber::Release()
{
	if(!PhysicsHandle)
	{
		return;
	}
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp,Error,TEXT("Physics handle not found on %s!"), *GetOwner()->GetName()); 
	}
}

void UGrabber::CheckInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if(InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
	}
}

FHitResult UGrabber::GetObject()
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerPosition(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	return Hit;
}

FVector UGrabber::GetPlayerReach()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);

	FVector LineTraceDirection = PlayerViewPointRotation.Vector();

	return PlayerViewPointLocation + LineTraceDirection*Reach;
}

FVector UGrabber::GetPlayerPosition()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FRotator UGrabber::GetPlayerRotation()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);

	return PlayerViewPointRotation;
}