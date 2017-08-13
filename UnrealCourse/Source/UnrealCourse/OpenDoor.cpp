// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCourse.h"
#include "OpenDoor.h"

#define out

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

float UOpenDoor::GetTotalMassOnPlate () {
    float totalMass = 0.0f;
    
    TArray<AActor*> actors;
    this->pressurePlate->GetOverlappingActors (out actors);
    
    for (AActor* actor : actors) {
        totalMass += actor->FindComponentByClass<UPrimitiveComponent> ()->GetMass();
    }
    
    return totalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (this->pressurePlate == nullptr) {
        return;
    }
    
    if (this->GetTotalMassOnPlate () > this->triggerMass) {
        this->onOpen.Broadcast ();
    } else {
        this->onClose.Broadcast ();
    }
}

