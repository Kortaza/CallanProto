// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Components/SceneCaptureComponent2D.h"
#include "PawnVR.generated.h"

class UInputComponent;

//UENUM(BlueprintType)
enum class EZoomLevel : uint8
{
	ZOOM_x1		UMETA(DisplayName = "Zoom x2"),
	ZOOM_x2		UMETA(DisplayName = "Zoom x2"),
	ZOOM_x4		UMETA(DisplayName = "Zoom x4"),
	ZOOM_x8		UMETA(DisplayName = "Zoom x8"),
	ZOOM_x16	UMETA(DisplayName = "Zoom x16"),
};

/**
 * 
 */
UCLASS(config = Game)
class VRPROTO_API APawnVR : public AGamePawn
{
	GENERATED_BODY()
	
public: // Functionality
	APawnVR(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: // Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* VR_Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera_VR;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMotionControllerComponent* MotionController_Left;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMotionControllerComponent* MotionController_Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VisorZoom")
		UStaticMeshComponent* VisorMesh_ZoomPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VisorZoom")
		UStaticMeshComponent* VisorMesh_ObscuringPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VisorZoom")
		USceneCaptureComponent2D* VisorCapture;

protected: // Functions
	virtual void BeginPlay() override;
	virtual void Movement_Forward(float value);
	virtual void Movement_Right(float value);
	virtual void View_X(float value);
	virtual void View_Y(float value);
	virtual void ActivateVisor_Pressed();
	virtual void ActivateVisor_Released();
	virtual void Fire_Pressed();
	virtual void Fire_Released();

	virtual void ZoomChangeUp_Pressed();
	virtual void ZoomChangeDown_Pressed();
	void UpdateCaptureFOV();

protected: // Variables
	EZoomLevel ZoomLevel;
};
