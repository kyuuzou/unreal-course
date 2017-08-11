// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCourse.h"
#include "PositionReporter.h"

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();
    
    AActor* owner = this->GetOwner ();
    FString name = owner->GetName ();
    FVector position = owner->GetActorLocation ();
    FString alternatePosition = owner->GetTransform ().GetLocation ().ToString ();
    UE_LOG (LogTemp, Warning, TEXT ("%s is at (%f, %f, %f)"), *name, position.X, position.Y, position.Z);
    UE_LOG (LogTemp, Warning, TEXT ("%s is at %s"), *name, *alternatePosition);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

