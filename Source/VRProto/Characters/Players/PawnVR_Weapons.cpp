// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnVR_Weapons.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Classes/Engine/TextureRenderTarget2D.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"

#include "../../Weapons/SniperRifle.h"

// Sets default values
APawnVR_Weapons::APawnVR_Weapons(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Find the relevant meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh>PlaneMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));

	// VR Origin creation and basic setup
	VR_Origin = CreateDefaultSubobject<USceneComponent>(TEXT("VR_Origin"));
	VR_Origin->SetupAttachment(GetRootComponent());

	// The Main VR Camera creation and basic setup
	Camera_VR = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_VR"));
	Camera_VR->SetupAttachment(VR_Origin);

	// Setup the Motion Controllers for VR
	MotionController_Left = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController_Left"));
	MotionController_Left->MotionSource = FXRMotionControllerBase::LeftHandSourceId;
	MotionController_Left->SetupAttachment(RootComponent);
	MotionController_Right = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController_Right"));
	MotionController_Right->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	MotionController_Right->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APawnVR_Weapons::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world)
	{
		FAttachmentTransformRules attachmentRules(EAttachmentRule::KeepWorld, true);

		// Spawn and attach Weapon (Right Hand)
		FVector spawnLoc = MotionController_Right->GetComponentLocation();
		FRotator spawnRot = MotionController_Right->GetComponentRotation();
		Weapon = (AWeapon*)world->SpawnActor(StartingWeapon, &spawnLoc, &spawnRot);	
		Weapon->AttachToComponent(MotionController_Right, attachmentRules);
		Weapon->SetActorRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

		// Spawn and attach Left Hand
		spawnLoc = MotionController_Left->GetComponentLocation();
		spawnRot = MotionController_Left->GetComponentRotation();
		LeftHand = (AHandVR*)world->SpawnActor(HandTemplate, &spawnLoc, &spawnRot);
		LeftHand->AttachToComponent(MotionController_Left, attachmentRules);
		LeftHand->SetHandType(EControllerHand::Left);
		//LeftHand->SetActorRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	}
}

// Called every frame
void APawnVR_Weapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnVR_Weapons::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement functionality
	PlayerInputComponent->BindAxis("Movement_Forward", this, &APawnVR_Weapons::Movement_Forward);
	PlayerInputComponent->BindAxis("Movement_Right", this, &APawnVR_Weapons::Movement_Right);
	PlayerInputComponent->BindAxis("View_X", this, &APawnVR_Weapons::View_X);
	PlayerInputComponent->BindAxis("View_Y", this, &APawnVR_Weapons::View_Y);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnVR_Weapons::Fire_Pressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APawnVR_Weapons::Fire_Released);
	PlayerInputComponent->BindAction<FZoomDelegate>("Zoom Change Up", IE_Pressed, this, &APawnVR_Weapons::ZoomChangeUp_Pressed, 1);
	PlayerInputComponent->BindAction<FZoomDelegate>("Zoom Change Down", IE_Pressed, this, &APawnVR_Weapons::ZoomChangeDown_Pressed, 1);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APawnVR_Weapons::Reload_Pressed);
}

void APawnVR_Weapons::Movement_Forward(float value)
{
	if (value != 0.0f)
	{
		// Add movement in the direction
		AddMovementInput(Camera_VR->GetForwardVector(), value);
	}
}

void APawnVR_Weapons::Movement_Right(float value)
{
	if (value != 0.0f)
	{
		// Add movement in the direction
		AddMovementInput(Camera_VR->GetRightVector(), value);
	}
}

void APawnVR_Weapons::View_X(float value)
{
	if (value != 0.0f)
	{
		AddControllerYawInput(value);
	}
}

void APawnVR_Weapons::View_Y(float value)
{
	if (value != 0.0f)
	{
		AddControllerPitchInput(value);
	}
}

void APawnVR_Weapons::Fire_Pressed()
{
	Weapon->Fire_Pressed();
}

void APawnVR_Weapons::Fire_Released()
{
	Weapon->Fire_Released();
}


void APawnVR_Weapons::ZoomChangeUp_Pressed(int value)
{
	Weapon->ZoomChangeUp_Pressed(value);
}

void APawnVR_Weapons::ZoomChangeDown_Pressed(int value)
{
	Weapon->ZoomChangeDown_Pressed(value);
}

void APawnVR_Weapons::Reload_Pressed()
{
	Weapon->Reload_Pressed();
}
