// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Components/SceneCaptureComponent2D.h"
#include "PawnVR.generated.h"

class UInputComponent;

//UENUM(BlueprintType)


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
		UStaticMeshComponent* VisorMesh_Crosshair;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VisorZoom")
		USceneCaptureComponent2D* VisorCapture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
		USoundBase* AudioSniperShot;

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
	void UpdateCaptureFOV(float changeTime);
	void UpdateZoom(float DeltaTime);

protected: // Variables

	// Zoom Variables
	EZoomLevel ZoomLevel;
	bool ZoomActive;
	float FOV_Start;
	float FOV_End;
	float ZoomChangeSpeed;
	float ZoomChangeTime;
	float ZoomChangeLerp;
	bool UpdatingZoomLevel;

	//
	float MaxRange;
	float Damage;
};
