// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCOURSE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY (EditAnywhere)
    float reach = 100.0f;
	
    APlayerController* playerController;
    UPhysicsHandleComponent* physicsHandle = nullptr;
    UInputComponent* inputComponent = nullptr;
    
    FHitResult GetFirstPhysicsBodyInReach ();
    FVector GetReachLineEnd ();
    void InitializeInputComponent ();
    void InitializePhysicsHandleComponent ();
    void Grab ();
    void Release ();
    
};
