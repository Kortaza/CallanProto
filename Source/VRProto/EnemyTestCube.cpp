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

}

