// Copyright 2021, Srujan Pant. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()



public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//User defined variables
	float OpenAngle;
	float InitialYaw;
	float TargetYaw;
	float DoorLastOpened = 0.f;
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoors = 50.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;	

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	//User defined functions
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors();
	void FindAudioComponent();
	void FindPressurePlate();
};
