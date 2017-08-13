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

void UOpenDoor::Open () {
    AActor* owner = this->GetOwner ();
    
    FRotator rotation = FRotator (0.0f, this->openAngle, 0.0f);
    owner->SetActorRotation (rotation);
}

void UOpenDoor::Close () {
    AActor* owner = this->GetOwner ();
    
    FRotator rotation = FRotator (0.0f, 0.0f, 0.0f);
    owner->SetActorRotation (rotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (this->pressurePlate == nullptr) {
        return;
    }
    
    float currentTime = this->GetWorld ()->GetTimeSeconds();
    
    if (this->GetTotalMassOnPlate () > 40.0f) {
        this->Open ();
        this->lastOpenTime = currentTime;
    }
    
    if (currentTime > this->lastOpenTime + this->closeDelay) {
        this->Close ();
    }
}

