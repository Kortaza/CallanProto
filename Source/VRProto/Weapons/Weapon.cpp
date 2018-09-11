// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a root component that acts and the actors origin
	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(GetRootComponent());

	// Create a mesh component accessible in C++ but populated in Blueprint
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(Origin);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up Magazine information
	CurrentMagazineAmmo = MagazineSize;
	FireDelayTime = 0.0f;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Updating Fire Delay
	UpdateFireDelay(DeltaTime);
}


void AWeapon::Fire_Pressed()
{
	//if (AudioSniperShot)
	//{
	//	UGameplayStatics::PlaySoundAtLocation(this, AudioSniperShot, GetActorLocation());
	//}
	//
	//FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	//RV_TraceParams.bTraceComplex = true;
	//RV_TraceParams.bTraceAsyncScene = true;
	//RV_TraceParams.bReturnPhysicalMaterial = false;
	//
	////Re-initialize hit info
	//FHitResult RV_Hit(ForceInit);
	//
	//FVector Start = Camera_VR->GetComponentLocation();
	//FVector End = Camera_VR->GetForwardVector() * MaxRange + Start;
	//
	////call GetWorld() from within an actor extending class
	//GetWorld()->LineTraceSingleByChannel(
	//	RV_Hit,				//result
	//	Start,				//start
	//	End,				//end
	//	ECC_Pawn,			//collision channel
	//	RV_TraceParams
	//);
	//
	//AEnemy* target = Cast<AEnemy>(RV_Hit.Actor);
	//if (target)
	//{
	//	target->UpdateHealth(Damage);
	//}
}

void AWeapon::Fire_Released()
{

}


void AWeapon::ZoomChangeUp_Pressed()
{

}

void AWeapon::ZoomChangeDown_Pressed()
{

}

void AWeapon::UpdateCaptureFOV(float changeTime)
{

}

void AWeapon::UpdateZoom(float DeltaTime)
{

}


void AWeapon::UpdateFireDelay(float DeltaTime)
{
	if (FireDelayActive)
	{
		FireDelayTime -= DeltaTime;
		if (FireDelayTime <= 0.0f)
		{
			FireDelayActive = false;
		}
	}
}

void AWeapon::Reload_Pressed()
{
	CurrentMagazineAmmo = MagazineSize;
}
