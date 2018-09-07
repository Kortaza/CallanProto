// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnVR.h"
#include "Engine/Classes/Engine/TextureRenderTarget2D.h"

// Sets default values
APawnVR::APawnVR()
	: Super()
{
	// Find the relevant meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh>PlaneMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));

	// VR Origin creation and basic setup
	VR_Origin = CreateDefaultSubobject<USceneComponent>(TEXT("VR_Origin"));
	VR_Origin->SetupAttachment(GetRootComponent());
	VR_Origin->RelativeLocation = FVector(0.0f, 0.0f, 64.0f);
	
	// The Main VR Camera creation and basic setup
	Camera_VR = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_VR"));
	Camera_VR->SetupAttachment(VR_Origin);

	// Creating and placing the Visor - Zoom Panel
	VisorMesh_ZoomPanel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisorMesh_ZoomPanel"));
	VisorMesh_ZoomPanel->SetupAttachment(Camera_VR);
	VisorMesh_ZoomPanel->SetStaticMesh(PlaneMesh.Object);	
	VisorMesh_ZoomPanel->SetRelativeLocation(FVector(200.0f, 0.0f, 0.0f));
	VisorMesh_ZoomPanel->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
	VisorMesh_ZoomPanel->SetRelativeScale3D(FVector(1.7777f, 1.0f, 1.0f));
	VisorMesh_ZoomPanel->SetVisibility(false, true);
	
	// Creating and placing the Visor - Obscuring Panel to create relative space that is unchanging when zoomed in
	VisorMesh_ObscuringPanel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisorMesh_ObscuringPanel"));
	VisorMesh_ObscuringPanel->SetupAttachment(VisorMesh_ZoomPanel);
	VisorMesh_ObscuringPanel->SetStaticMesh(PlaneMesh.Object);
	VisorMesh_ObscuringPanel->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
	VisorMesh_ObscuringPanel->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	VisorMesh_ObscuringPanel->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	VisorMesh_ObscuringPanel->SetVisibility(false, true);

	// Creating and placing the Capture component for the zoom capture
	VisorCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Visor_Capture"));
	VisorCapture->SetupAttachment(Camera_VR);
	VisorCapture->SetRelativeLocation(FVector(1.0f, 0.0f, 0.0f));
	VisorCapture->HideComponent(VisorMesh_ZoomPanel);
	VisorCapture->HideComponent(VisorMesh_ObscuringPanel);

}

// Called when the game starts or when spawned
void APawnVR::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnVR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement functionality
	PlayerInputComponent->BindAxis("Movement_Forward", this, &APawnVR::Movement_Forward);
	PlayerInputComponent->BindAxis("Movement_Right", this, &APawnVR::Movement_Right);
}

void APawnVR::Movement_Forward(float value)
{
	if (value != 0.0f)
	{
		// Add movement in the direction
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void APawnVR::Movement_Right(float value)
{
	if (value != 0.0f)
	{
		// Add movement in the direction
		AddMovementInput(GetActorRightVector(), value);
	}
}

void APawnVR::View_X(float value)
{

}

void APawnVR::View_Y(float value)
{

}

void APawnVR::LeftTrigger_Pressed(float value)
{

}

void APawnVR::LeftTrigger_Released(float value)
{

}

void APawnVR::RightTrigger_Pressed(float value)
{

}

void APawnVR::RightTrigger_Released(float value)
{

}


