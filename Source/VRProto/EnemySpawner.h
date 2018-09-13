// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class VRPROTO_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	// Functionality 
	AEnemySpawner();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SpawnEnemy();

public :  // Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Properties")
		float FirstWaveSpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Properties")
		float SpawnRate;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blueprint References")
		class AProtectionGoal* ProtectionGoal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blueprint References")
		TSubclassOf<class AEnemy> EnemySpawns;

	

protected:
	float TimeUntilSpawn;
	

	
	
};
