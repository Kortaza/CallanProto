// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyTestCube.generated.h"

/**
 * 
 */
UCLASS()
class VRPROTO_API AEnemyTestCube : public AEnemy
{
	GENERATED_BODY()
	
public:
	AEnemyTestCube(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
