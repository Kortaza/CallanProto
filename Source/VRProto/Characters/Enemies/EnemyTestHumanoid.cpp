// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTestHumanoid.h"

// Sets default values
AEnemyTestHumanoid::AEnemyTestHumanoid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemyTestHumanoid::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyTestHumanoid::Tick(float DeltaTime)
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


