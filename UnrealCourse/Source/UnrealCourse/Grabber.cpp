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

    this->playerController = this->GetWorld()->GetFirstPlayerController();
    
    this->inputComponent = this->GetOwner ()->FindComponentByClass<UInputComponent> ();

    this->InitializePhysicsHandleComponent ();
    this->InitializeInputComponent ();
}

void UGrabber::InitializeInputComponent () {
    if (this->inputComponent == nullptr) {
        UE_LOG (LogTemp, Error, TEXT ("InputComponent not found on %s"), *this->GetOwner()->GetName());
    } else {
        this->inputComponent->BindAction ("Grab", IE_Pressed, this, &UGrabber::Grab);
        this->inputComponent->BindAction ("Grab", IE_Released, this, &UGrabber::Release);
    }
}

void UGrabber::InitializePhysicsHandleComponent () {
    this->physicsHandle = this->GetOwner ()->FindComponentByClass<UPhysicsHandleComponent> ();
    
    if (this->physicsHandle == nullptr) {
        UE_LOG (LogTemp, Error, TEXT ("PhysicsHandleComponent not found on %s"), *this->GetOwner()->GetName());
    }
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach () {
    FVector location;
    FRotator rotation;
    
    this->playerController->GetPlayerViewPoint (out location, out rotation);
    
    FVector reachLineEnd = this->GetReachLineEnd ();
    
    UWorld* world = this->GetWorld();
    
    DrawDebugLine (world, location, reachLineEnd, FColor::Red, false, 0.0f, 0.0f, 10.0f);
    
    FHitResult hit;
    
    FCollisionQueryParams traceParameters = FCollisionQueryParams (FName (TEXT ("")), false, this->GetOwner ());

    world->LineTraceSingleByObjectType (
        out hit,
        location,
        reachLineEnd,
        FCollisionObjectQueryParams (ECollisionChannel::ECC_PhysicsBody),
        traceParameters
    );
    
    return hit;
}

FVector UGrabber::GetReachLineEnd () {
    FVector location;
    FRotator rotation;
    
    this->playerController->GetPlayerViewPoint (out location, out rotation);
    
    return location + rotation.Vector() * this->reach;
}

void UGrabber::Grab () {
    FHitResult hitResult = this->GetFirstPhysicsBodyInReach ();
    AActor* actorHit = hitResult.GetActor ();
    
    if (actorHit == nullptr) {
        return;
    }

    this->physicsHandle->GrabComponentAtLocation (
        hitResult.GetComponent (),
        NAME_None,
        actorHit->GetActorLocation ()
    );
}

void UGrabber::Release () {
    if (this->physicsHandle->GrabbedComponent != nullptr) {
        this->physicsHandle->ReleaseComponent ();
    }
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (this->physicsHandle->GrabbedComponent != nullptr) {
        FVector reachLineEnd = this->GetReachLineEnd ();
        physicsHandle->SetTargetLocation (reachLineEnd);
    }
}

