// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "SniperRifle.generated.h"



/**
 * 
 */
UCLASS()
class VRPROTO_API ASniperRifle : public AWeapon
{
	GENERATED_BODY()
	
public: // Functionality
	ASniperRifle();
	virtual void Tick(float DeltaTime) override;
	virtual void Fire_Pressed() override;
	virtual void Fire_Released() override;
	virtual void ZoomChangeUp_Pressed() override;
	virtual void ZoomChangeDown_Pressed() override;

protected: // Functionality
	virtual void BeginPlay() override;

	
	virtual void UpdateCaptureFOV(float changeTime) override;
	virtual void UpdateZoom(float DeltaTime) override;

public: // Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scope Components")
		UStaticMeshComponent* Scope;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scope Components")
		UStaticMeshComponent* Crosshair;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scope Components")
		USceneCaptureComponent2D* ScopeCapture;

protected: // Variables
};
