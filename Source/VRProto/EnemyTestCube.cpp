// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTestCube.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AEnemyTestCube::AEnemyTestCube(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetStaticMesh(MeshAsset.Object);
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
		FVector movement = direction * 1000.0f * DeltaTime;

		FVector newLoc = movement + GetActorLocation();
		SetActorLocation(newLoc);
	}

}

