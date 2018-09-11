// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GamePawn.generated.h"

enum class EZoomLevel : uint8
{
	ZOOM_x1		UMETA(DisplayName = "Zoom x1"),
	ZOOM_x2		UMETA(DisplayName = "Zoom x2"),
	ZOOM_x4		UMETA(DisplayName = "Zoom x4"),
	ZOOM_x8		UMETA(DisplayName = "Zoom x8"),
	ZOOM_x16	UMETA(DisplayName = "Zoom x16"),
	ZOOM_x32	UMETA(DisplayName = "Zoom x32"),
};

UCLASS()
class VRPROTO_API AGamePawn : public ACharacter
{
	GENERATED_BODY()

public:
	AGamePawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: // Functionality
	virtual void BeginPlay() override;
	virtual void UpdateHealth(float delta);
	virtual void Death();

public: // Variables
	float MaxHealth;
	float CurrentHealth;
};
