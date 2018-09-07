// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnVR.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Classes/Engine/TextureRenderTarget2D.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"

// Sets default values
APawnVR::APawnVR(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

	// Setup the Motion Controllers for VR
	MotionController_Left = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController_Left"));
	MotionController_Right->MotionSource = FXRMotionControllerBase::LeftHandSourceId;
	MotionController_Left->SetupAttachment(RootComponent);
	MotionController_Right = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController_Right"));
	MotionController_Right->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	MotionController_Right->SetupAttachment(RootComponent);
	
	// Creating and placing the Visor - Zoom Panel
	VisorMesh_ZoomPanel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisorMesh_ZoomPanel"));
	VisorMesh_ZoomPanel->SetupAttachment(Camera_VR);
	VisorMesh_ZoomPanel->SetStaticMesh(PlaneMesh.Object);	
	VisorMesh_ZoomPanel->SetRelativeLocation(FVector(180.0f, 0.0f, 0.0f));
	VisorMesh_ZoomPanel->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
	VisorMesh_ZoomPanel->SetRelativeScale3D(FVector(1.7777f, 1.0f, 1.0f));
	VisorMesh_ZoomPanel->SetVisibility(false, true);
	
	// Creating and placing the Visor - Obscuring Panel to create relative space that is unchanging when zoomed in
	VisorMesh_ObscuringPanel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisorMesh_ObscuringPanel"));
	VisorMesh_ObscuringPanel->SetupAttachment(VisorMesh_ZoomPanel);
	VisorMesh_ObscuringPanel->SetStaticMesh(PlaneMesh.Object);
	VisorMesh_ObscuringPanel->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
	VisorMesh_ObscuringPanel->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	VisorMesh_ObscuringPanel->SetRelativeScale3D(FVector(4.0f, 4.0f, 4.0f));
	VisorMesh_ObscuringPanel->SetVisibility(false, true);

	// Creating and placing the Capture component for the zoom capture
	VisorCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Visor_Capture"));
	VisorCapture->SetupAttachment(Camera_VR);
	VisorCapture->SetRelativeLocation(FVector(1.0f, 0.0f, 0.0f));
	VisorCapture->HideComponent(VisorMesh_ZoomPanel);
	VisorCapture->HideComponent(VisorMesh_ObscuringPanel);

	// Setup base variables
	ZoomLevel = EZoomLevel::ZOOM_x1;
}

// Called when the game starts or when spawned
void APawnVR::BeginPlay()
{
	Super::BeginPlay();

	UpdateCaptureFOV();
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
	PlayerInputComponent->BindAxis("View_X", this, &APawnVR::View_X);
	PlayerInputComponent->BindAxis("View_Y", this, &APawnVR::View_Y);

	PlayerInputComponent->BindAction("Activate Visor", IE_Pressed, this, &APawnVR::ActivateVisor_Pressed);
	PlayerInputComponent->BindAction("Activate Visor", IE_Released, this, &APawnVR::ActivateVisor_Released);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnVR::Fire_Pressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APawnVR::Fire_Released);
	PlayerInputComponent->BindAction("Zoom Change Up", IE_Pressed, this, &APawnVR::ZoomChangeUp_Pressed);
	PlayerInputComponent->BindAction("Zoom Change Down", IE_Pressed, this, &APawnVR::ZoomChangeDown_Pressed);
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
	if (value != 0.0f)
	{
		AddControllerYawInput(value);
	}
}

void APawnVR::View_Y(float value)
{
	if (value != 0.0f)
	{
		AddControllerPitchInput(value);
	}
}

void APawnVR::ActivateVisor_Pressed()
{
	VisorMesh_ZoomPanel->SetVisibility(true, true);
}

void APawnVR::ActivateVisor_Released()
{
	VisorMesh_ZoomPanel->SetVisibility(false, true);
}

void APawnVR::Fire_Pressed()
{
	
}

void APawnVR::Fire_Released()
{
	
}

void APawnVR::ZoomChangeUp_Pressed()
{
	if (ZoomLevel < EZoomLevel::ZOOM_x16)
	{
		ZoomLevel = (EZoomLevel)((int)ZoomLevel + 1);
	}
	UpdateCaptureFOV();
}

void APawnVR::ZoomChangeDown_Pressed()
{
	if (ZoomLevel > EZoomLevel::ZOOM_x1)
	{
		ZoomLevel = (EZoomLevel)((int)ZoomLevel - 1);
	}
	UpdateCaptureFOV();
}

void APawnVR::UpdateCaptureFOV()
{
	switch (ZoomLevel)
	{
	case EZoomLevel::ZOOM_x2:
		VisorCapture->FOVAngle = 90.0f * 0.25f;
		break;
	case EZoomLevel::ZOOM_x4:
		VisorCapture->FOVAngle = 90.0f * 0.125f;
		break;
	case EZoomLevel::ZOOM_x8:
		VisorCapture->FOVAngle = 90.0f * 0.0625f;
		break;
	case EZoomLevel::ZOOM_x16:
		VisorCapture->FOVAngle = 90.0f * 0.03125f;
		break;
	case EZoomLevel::ZOOM_x1: // Fall Through		
	default:
		VisorCapture->FOVAngle = 90.0f * 0.5f;
		break;
	}
}
