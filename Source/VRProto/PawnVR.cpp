// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnVR.h"

// Sets default values
APawnVR::APawnVR()
	: Super()
{
	VR_Origin = CreateDefaultSubobject<USceneComponent>(TEXT("VR_Origin"));
	VR_Origin->SetupAttachment(GetRootComponent());
	VR_Origin->RelativeLocation = FVector(0.0f, 0.0f, 64.0f);
	
	Camera_VR = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_VR"));
	Camera_VR->SetupAttachment(VR_Origin);

	Camera_Sniper = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_Sniper"));
	Camera_Sniper->SetupAttachment(Camera_VR);
}

// Called when the game starts or when spawned
void APawnVR::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APawnVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnVR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement functionality
	PlayerInputComponent->BindAxis("Movement_Forward", this, &APawnVR::Movement_Forward);
	PlayerInputComponent->BindAxis("Movement_Right", this, &APawnVR::Movement_Right);
}

void APawnVR::Movement_Forward(float value)
{
	if (value != 0.0f)
	{
		// Add movement in the direction
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void APawnVR::Movement_Right(float value)
{
	if (value != 0.0f)
	{
		// Add movement in the direction
		AddMovementInput(GetActorRightVector(), value);
	}
}


