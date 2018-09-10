// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

//
#include "ProtectionGoal.h"

// Spawnable Enemies
#include "EnemyTestCube.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating and Adding the SpawnArea mesh
	SpawnArea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TimeUntilSpawn = FirstWaveSpawnDelay;

	// Get the Protection Goal object
	TSubclassOf<AProtectionGoal> goalClass;
	goalClass = AProtectionGoal::StaticClass();
	TArray<AActor*> arrayGoal;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), goalClass, arrayGoal);
	ProtectionGoal = (AProtectionGoal*)arrayGoal[0];
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeUntilSpawn -= DeltaTime;
	if (TimeUntilSpawn < 0.0f)
	{
		SpawnEnemy();
		TimeUntilSpawn += SpawnRate;
	}
}

void AEnemySpawner::SpawnEnemy()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FVector spawnLoc = GetActorLocation();
		spawnLoc.Y = FMath::RandRange(spawnLoc.Y - (100 * SpawnArea->GetComponentScale().Y), spawnLoc.Y + (100 * SpawnArea->GetComponentScale().Y));
		FRotator spawnRot = GetActorRotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEnemy* newEnemy = world->SpawnActor<AEnemy>(EnemySpawns, spawnLoc, spawnRot, ActorSpawnParams);
		newEnemy->SetTarget((AActor*)ProtectionGoal);
	}
}
