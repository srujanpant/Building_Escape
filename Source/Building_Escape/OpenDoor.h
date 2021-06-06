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

	float OpenAngle;
	float InitialYaw;
	float TargetYaw;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;	

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	void OpenDoor(float DeltaTime);
};
