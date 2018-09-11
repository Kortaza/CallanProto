// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GamePawn.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class VRPROTO_API AEnemy : public AGamePawn
{
	GENERATED_BODY()

public:
	AEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;
	virtual void SetTarget(AActor* target);

protected:
	virtual void BeginPlay() override;
	virtual void Death() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* BaseMesh;

protected:
	AActor* CurrentTarget;
};
