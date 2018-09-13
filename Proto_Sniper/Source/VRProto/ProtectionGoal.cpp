// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtectionGoal.h"


// Sets default values
AProtectionGoal::AProtectionGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AProtectionGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProtectionGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

