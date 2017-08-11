// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCOURSE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent (
        float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction
    ) override;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    void Close ();
    void Open ();

    UPROPERTY (VisibleAnywhere)
    float openAngle = 90.0f;
    
    UPROPERTY (EditAnywhere)
    ATriggerVolume* pressurePlate;
    
    UPROPERTY (EditAnywhere)
    float closeDelay = 1.0f;
    
    float lastOpenTime;
    
    APawn* playerPawn;
};
