// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandVR.generated.h"

UCLASS()
class VRPROTO_API AHandVR : public AActor
{
	GENERATED_BODY()
	
public:		// Functionality
	AHandVR();
	virtual void Tick(float DeltaTime) override;
	virtual void SetHandType(EControllerHand type);

protected:	// Functionality
	virtual void BeginPlay() override;

public:	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent* HandMesh;

protected:	// Variables
	EControllerHand HandType;
	
};
