// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCourse.h"
#include "Grabber.h"

#define out

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

	UE_LOG (LogTemp, Warning, TEXT("Grabber reporting for duty!"));
    
    this->playerController = this->GetWorld()->GetFirstPlayerController();
    
    this->physicsHandle = this->GetOwner ()->FindComponentByClass<UPhysicsHandleComponent> ();
    this->inputComponent = this->GetOwner ()->FindComponentByClass<UInputComponent> ();

    if (this->physicsHandle == nullptr) {
        UE_LOG (LogTemp, Error, TEXT ("PhysicsHandleComponent not found on %s"), *this->GetOwner()->GetName());
    }
    
    if (this->inputComponent == nullptr) {
        UE_LOG (LogTemp, Error, TEXT ("InputComponent not found on %s"), *this->GetOwner()->GetName());
    } else {
        this->inputComponent->BindAction ("Grab", IE_Pressed, this, &UGrabber::Grab);
        this->inputComponent->BindAction ("Grab", IE_Released, this, &UGrabber::Release);
    }
}

void UGrabber::Grab () {
    UE_LOG(LogTemp, Display, TEXT ("Grab pressed!"));
}

void UGrabber::Release () {
    UE_LOG(LogTemp, Display, TEXT ("Grab released!"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector location;
    FRotator rotation;
    
    this->playerController->GetPlayerViewPoint (out location, out rotation);
    
    //UE_LOG (LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *location.ToString(), *rotation.ToString());
    
    FVector lineTraceEnd = location + rotation.Vector() * this->reach;
    
    UWorld* world = this->GetWorld();
    
    DrawDebugLine (
        world,
        location,
        lineTraceEnd,
        FColor::Red,
        false,
        0.0f,
        0.0f,
        10.0f
    );
    
    FHitResult hit;
    
    FCollisionQueryParams traceParameters = FCollisionQueryParams (FName (TEXT ("")), false, this->GetOwner ());

    bool hitSomething = world->LineTraceSingleByObjectType (
        out hit,
        location,
        lineTraceEnd,
        FCollisionObjectQueryParams (ECollisionChannel::ECC_PhysicsBody),
        traceParameters
    );
    
    if (hitSomething) {
        UE_LOG (LogTemp, Display, TEXT ("Hit: %s"), *hit.Actor->GetName());
    }
}

