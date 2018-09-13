// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"


// Sets default values
AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::SetTarget(AActor* target)
{
	CurrentTarget = target;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::Death()
{
	Destroy();
}
