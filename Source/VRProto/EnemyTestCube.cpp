// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTestCube.h"

// Sets default values
AEnemyTestCube::AEnemyTestCube(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemyTestCube::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyTestCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTarget)
	{
		FVector targetLoc = CurrentTarget->GetActorLocation();
		FVector direction = (targetLoc - GetActorLocation());
		direction.Normalize();
		FVector movement = direction * 300.0f * DeltaTime;

		FVector newLoc = movement + GetActorLocation();
		SetActorLocation(newLoc);
	}

}

