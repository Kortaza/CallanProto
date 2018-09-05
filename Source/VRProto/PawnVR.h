// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "PawnVR.generated.h"

/**
 * 
 */
UCLASS()
class VRPROTO_API APawnVR : public AGamePawn
{
	GENERATED_BODY()
	
public: // Functionality
	APawnVR();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: // Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		USceneComponent* VR_Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		UCameraComponent* Camera_VR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		UCameraComponent* Camera_Sniper;

protected:
	virtual void BeginPlay() override;
	virtual void Movement_Forward(float value);
	virtual void Movement_Right(float value);
};
