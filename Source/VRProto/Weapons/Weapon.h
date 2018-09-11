// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

enum class EZoom_Weapon : uint8
{
	ZOOM_x1		UMETA(DisplayName = "Zoom x1"),
	ZOOM_x2		UMETA(DisplayName = "Zoom x2"),
	ZOOM_x4		UMETA(DisplayName = "Zoom x4"),
	ZOOM_x8		UMETA(DisplayName = "Zoom x8"),
	ZOOM_x16	UMETA(DisplayName = "Zoom x16"),
	ZOOM_x32	UMETA(DisplayName = "Zoom x32"),
};

UCLASS()
class VRPROTO_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:		// Functionality
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void Fire_Pressed();
	virtual void Fire_Released();
	virtual void ZoomChangeUp_Pressed();
	virtual void ZoomChangeDown_Pressed();
	virtual void Reload_Pressed();

protected:	// Functionality
	virtual void BeginPlay() override;

	virtual void UpdateCaptureFOV(float changeTime);
	virtual void UpdateZoom(float DeltaTime);
	virtual void UpdateFireDelay(float DeltaTime);

public:		// Variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (DisplayName = "Fire"))
		USoundBase* Audio_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
		USoundBase* Audio_DryFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zoom Properties")
		float ZoomChangeSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
		int MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
		float MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
		float FireDelay;

protected:	// Variables
	
	// Zoom Variables
	EZoom_Weapon ZoomLevel;
	float FOV_Start;
	float FOV_End;
	float ZoomChangeTime;
	float ZoomChangeLerp;
	bool UpdatingZoomLevel;

	// Magazine Variables
	int CurrentMagazineAmmo;
	float FireDelayTime;
	bool FireDelayActive;
};
