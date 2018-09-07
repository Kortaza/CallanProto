// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Components/SceneCaptureComponent2D.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ViewPort")
		USceneComponent* VR_Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ViewPort")
		UCameraComponent* Camera_VR;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VisorZoom")
		UStaticMeshComponent* VisorMesh_ZoomPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VisorZoom")
		UStaticMeshComponent* VisorMesh_ObscuringPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VisorZoom")
		USceneCaptureComponent2D* VisorCapture;

protected:
	virtual void BeginPlay() override;
	virtual void Movement_Forward(float value);
	virtual void Movement_Right(float value);
	virtual void View_X(float value);
	virtual void View_Y(float value);
	virtual void LeftTrigger_Pressed(float value);
	virtual void LeftTrigger_Released(float value);
	virtual void RightTrigger_Pressed(float value);
	virtual void RightTrigger_Released(float value);
};
