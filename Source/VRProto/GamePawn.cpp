// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePawn.h"


// Sets default values
AGamePawn::AGamePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AGamePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGamePawn::UpdateHealth(float delta)
{
	CurrentHealth += delta;
	FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	if (CurrentHealth == 0.0f)
	{
		Death();
	}
}

void AGamePawn::Death()
{

}
