// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GamePawn.generated.h"

UCLASS()
class VRPROTO_API AGamePawn : public ACharacter
{
	GENERATED_BODY()

public:
	AGamePawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: // Functionality
	virtual void BeginPlay() override;
	virtual void UpdateHealth(float delta);
	virtual void Death();

protected: // Variables
	float MaxHealth;
	float CurrentHealth;
};
