// Fill out your copyright notice in the Description page of Project Settings.

#include "HandVR.h"


// Sets default values
AHandVR::AHandVR()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);

	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(Origin);
}

void AHandVR::SetHandType(EControllerHand type)
{
	HandType = type;
	if (HandType == EControllerHand::Left)
	{
		// Inverting the mesh and moving it to the opposite side to change the default right hand into a left hand
		HandMesh->RelativeScale3D.Z *= -1.0f;
		HandMesh->RelativeLocation.Y *= -1.0f;
	}
}

// Called when the game starts or when spawned
void AHandVR::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

