// Fill out your copyright notice in the Description page of Project Settings.

#include "SniperRifle.h"

#include "../Enemy.h"

#define Zoom_x1		90.0f / 10 / 1
#define Zoom_x2		90.0f / 10 / 2
#define Zoom_x4		90.0f / 10 / 4
#define Zoom_x8		90.0f / 10 / 8
#define Zoom_x16	90.0f / 10 / 16
#define Zoom_x32	90.0f / 10 / 32

// Sets default values
ASniperRifle::ASniperRifle()
{
	Scope = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scope"));
	Scope->SetupAttachment(BaseMesh);

	Crosshair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crosshair"));
	Crosshair->SetupAttachment(Scope);

	ScopeCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("ScopeCapture"));
	ScopeCapture->SetupAttachment(BaseMesh);
	ScopeCapture->HideComponent(BaseMesh);
	ScopeCapture->HideComponent(Crosshair);
}

// Called when the game starts or when spawned
void ASniperRifle::BeginPlay()
{
	Super::BeginPlay();

	// Set up Zoom
	ZoomLevel = EZoom_Weapon::ZOOM_x1;
	UpdateCaptureFOV(0.0f);

	
}

// Called every frame
void ASniperRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update Zoom level
	UpdateZoom(DeltaTime);
}

void ASniperRifle::Fire_Pressed()
{
	// Ensure there is ammo in current clip
	if (CurrentMagazineAmmo == 0)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Audio_DryFire, GetActorLocation());
		return;	// No ammo, do not continue
	}

	if (FireDelayActive)
	{
		return;	// Cannot fire, do not continue
	}

	// Continue if there is ammo available
	CurrentMagazineAmmo--;
	FireDelayActive = true;
	FireDelayTime = FireDelay;
	if (Audio_Fire)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Audio_Fire, GetActorLocation());
	}
	
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	
	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);
	
	FVector Start = ScopeCapture->GetComponentLocation();
	FVector End = ScopeCapture->GetForwardVector() * MaxRange + Start;
	
	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(
		RV_Hit,				//result
		Start,				//start
		End,				//end
		ECC_Pawn,			//collision channel
		RV_TraceParams
	);
	
	AEnemy* target = Cast<AEnemy>(RV_Hit.Actor);
	if (target)
	{
		target->UpdateHealth(Damage);
	}
}

void ASniperRifle::Fire_Released()
{

}


void ASniperRifle::ZoomChangeUp_Pressed()
{
	if (ZoomLevel < EZoom_Weapon::ZOOM_x32)
	{
		ZoomLevel = (EZoom_Weapon)((int)ZoomLevel + 1);
	}
	UpdateCaptureFOV(ZoomChangeSpeed);
}

void ASniperRifle::ZoomChangeDown_Pressed()
{
	if (ZoomLevel > EZoom_Weapon::ZOOM_x2)
	{
		ZoomLevel = (EZoom_Weapon)((int)ZoomLevel - 1);
	}
	UpdateCaptureFOV(ZoomChangeSpeed);
}

void ASniperRifle::UpdateCaptureFOV(float changeTime)
{
	UpdatingZoomLevel = true;
	ZoomChangeLerp = 0.0f;
	ZoomChangeTime = changeTime;
	
	FOV_Start = ScopeCapture->FOVAngle;
	
	switch (ZoomLevel)
	{
	case EZoom_Weapon::ZOOM_x2:
		FOV_End = Zoom_x2;
		break;
	case EZoom_Weapon::ZOOM_x4:
		FOV_End = Zoom_x4;
		break;
	case EZoom_Weapon::ZOOM_x8:
		FOV_End = Zoom_x8;
		break;
	case EZoom_Weapon::ZOOM_x16:
		FOV_End = Zoom_x16;
		break;
	case EZoom_Weapon::ZOOM_x32:
		FOV_End = Zoom_x32;
		break;
	case EZoom_Weapon::ZOOM_x1: // Fall Through		
	default:
		FOV_End = Zoom_x1;
		break;
	}
}

void ASniperRifle::UpdateZoom(float DeltaTime)
{
	if (UpdatingZoomLevel)
	{
		ZoomChangeLerp += DeltaTime * ZoomChangeSpeed;
		ZoomChangeLerp = FMath::Clamp(ZoomChangeLerp, 0.0f, 1.0f);
		ScopeCapture->FOVAngle = FMath::Lerp(FOV_Start, FOV_End, ZoomChangeLerp);
	
		if (ZoomChangeLerp >= 1.0f)
		{
			UpdatingZoomLevel = false;
		}
	}
}


