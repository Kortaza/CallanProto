// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GamePawn.h"

#include "HandVR.h"
#include "../../Weapons/Weapon.h"

#include "PawnVR_Weapons.generated.h"

/**
 * 
 */
UCLASS()
class VRPROTO_API APawnVR_Weapons : public AGamePawn
{
	GENERATED_BODY()

	DECLARE_DELEGATE_OneParam(FZoomDelegate, int);
	
public: // Functionality
	APawnVR_Weapons(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: // Functions
	virtual void BeginPlay() override;
	virtual void Movement_Forward(float value);
	virtual void Movement_Right(float value);
	virtual void View_X(float value);
	virtual void View_Y(float value);
	virtual void Fire_Pressed();
	virtual void Fire_Released();

	void ZoomChangeUp_Pressed(int value);
	void ZoomChangeDown_Pressed(int value);

	virtual void Reload_Pressed();

public: // Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* VR_Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera_VR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMotionControllerComponent* MotionController_Left;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMotionControllerComponent* MotionController_Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand Properties")
		TSubclassOf<AHandVR> HandTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand Properties")
		TSubclassOf<AWeapon> StartingWeapon;

protected:
	AWeapon* Weapon;
	AHandVR* LeftHand;
};
